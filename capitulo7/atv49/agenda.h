
#ifndef AGENDA_H
#define AGENDA_H

// Dados de uma missao
typedef struct {
    int id;
    char descricao[100];
} Missao;

// Tipos opacos
typedef struct Agenda Agenda;
typedef struct No No;

// Criacao e insercao
Agenda* criarAgenda(void);
int inserirNoInicio(Agenda* agenda, Missao m);
int inserirDepois(Agenda* agenda, No* referencia, Missao m);
int inserirAntes(Agenda* agenda, int idReferencia, Missao m);

// Busca
No* buscarMissao(const Agenda* agenda, int id);

// Remocoes
int removerPrimeiro(Agenda* agenda, Missao* removida);
int removerUltimo(Agenda* agenda, Missao* removida);
int removerPorID(Agenda* agenda, int id, Missao* removida);
int removerAntes(Agenda* agenda, int idReferencia, Missao* removida);
int removerDepois(Agenda* agenda, int idReferencia, Missao* removida);

// Atividade 48
void limparAgenda(Agenda* agenda);
int alterarMissao(Agenda* agenda, int id, const char* novaDescricao);

// Atividade 49
int tamanhoAgenda(const Agenda* agenda);
int inserirLote(Agenda* agenda, const Missao missoes[], int quantidade);

// Exibicao e destruicao
void exibirAgenda(const Agenda* agenda);
void destruirAgenda(Agenda* agenda);

#endif
