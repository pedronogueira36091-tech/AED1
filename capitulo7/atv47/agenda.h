#ifndef AGENDA_H
#define AGENDA_H

// Dados de uma missão
typedef struct {
    int id;
    char descricao[100];
} Missao;

// Tipo opaco para a Agenda (encapsulamento da lista encadeada)
typedef struct Agenda Agenda;

// Interface pública
Agenda* criarAgenda(void);
int inserirNoInicio(Agenda* agenda, Missao m);
void exibirAgenda(const Agenda* agenda);
void destruirAgenda(Agenda* agenda);
// Novas funções da atividade 46
int removerUltimo(Agenda* agenda, Missao* removida);
int removerPorID(Agenda* agenda, int id, Missao* removida);
// Novas funções da atividade 47
int removerAntes(Agenda* agenda, int idReferencia, Missao* removida);
int removerDepois(Agenda* agenda, int idReferencia, Missao* removida);

#endif // AGENDA_H