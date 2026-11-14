
#ifndef AGENDA_H
#define AGENDA_H

// Dados de uma missão
typedef struct {
    int id;
    char descricao[100];
} Missao;

// Tipos opacos
typedef struct Agenda Agenda;
typedef struct No No;

// Interface pública
Agenda* criarAgenda(void);
int inserirNoInicio(Agenda* agenda, Missao m);
No* buscarMissao(const Agenda* agenda, int id);
int inserirDepois(Agenda* agenda, No* referencia, Missao m);
void exibirAgenda(const Agenda* agenda);
void destruirAgenda(Agenda* agenda);

#endif // AGENDA_H
