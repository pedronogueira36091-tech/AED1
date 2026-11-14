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

#endif // AGENDA_H