
#ifndef AGENDA_H
#define AGENDA_H

// Dados de uma missao
typedef struct {
    int id;
    char descricao[100];
    int prioridade;
} Missao;

// Tipos opacos: detalhes internos ficam em agenda.c
typedef struct Agenda Agenda;
typedef struct No No;

// Criacao e insercao
Agenda* criarAgenda(void);
int inserirNoInicio(Agenda* agenda, Missao m);
int inserirDepois(Agenda* agenda, No* referencia, Missao m);
int inserirAntes(Agenda* agenda, int idReferencia, Missao m);

// Busca
No* buscarMissao(const Agenda* agenda, int id);

// Remocao
int removerPrimeiro(Agenda* agenda, Missao* removida);
int removerUltimo(Agenda* agenda, Missao* removida);
int removerPorID(Agenda* agenda, int id, Missao* removida);
int removerAntes(Agenda* agenda, int idReferencia, Missao* removida);
int removerDepois(Agenda* agenda, int idReferencia, Missao* removida);

// Alteracao e limpeza
void limparAgenda(Agenda* agenda);
int alterarMissao(Agenda* agenda, int id, const char* novaDescricao);

// Contagem e insercao em lote
int tamanhoAgenda(const Agenda* agenda);
int inserirLote(Agenda* agenda, const Missao missoes[], int quantidade);

// Ordenacao
void ordenarAgenda(Agenda* agenda);

// Persistencia
// Salva as missoes no arquivo binario.
int salvarAgenda(const Agenda* agenda, const char* nomeArquivo);

// Carrega as missoes preservando a ordem.
// Se o arquivo nao existir, mantem a agenda vazia.
int carregarAgenda(Agenda* agenda, const char* nomeArquivo);

// Exibicao e destruicao
void exibirAgenda(const Agenda* agenda);
void destruirAgenda(Agenda* agenda);

#endif
