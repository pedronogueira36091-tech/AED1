#ifndef AGENDA_H
#ifndef AGENDA_H
#define AGENDA_H

// Definição da estrutura Missao
typedef struct {
    int id;
    char descricao[100];
} Missao;

// Protótipos das funções expostas pela interface
Missao criarMissao(int id, const char* descricao);
void exibirMissao(Missao m);

#endif // AGENDA_H