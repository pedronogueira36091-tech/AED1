
#include <stdio.h>
#include "agenda.h"

int main() {
    Agenda* minhaAgenda = criarAgenda();

    if (minhaAgenda == NULL) {
        printf("Erro ao criar agenda.\n");
        return 1;
    }

    // Criando missoes
    Missao m1 = {1, "Explorar a caverna"};
    Missao m2 = {2, "Coletar ervas"};
    Missao m3 = {3, "Entregar a carta"};
    Missao m4 = {4, "Encontrar o tesouro"};

    // Inserindo missoes
    inserirNoInicio(minhaAgenda, m1);
    inserirNoInicio(minhaAgenda, m2);
    inserirNoInicio(minhaAgenda, m3);
    inserirNoInicio(minhaAgenda, m4);

    printf("\nAgenda inicial:");
    exibirAgenda(minhaAgenda);

    Missao removida;

    // Testando remocao por ID
    printf("\nRemovendo missao de ID 2...\n");

    if (removerPorID(minhaAgenda, 2, &removida)) {
        printf("Missao removida: %d - %s\n",
               removida.id, removida.descricao);
    } else {
        printf("Missao nao encontrada!\n");
    }

    printf("\nAgenda depois da remocao por ID:");
    exibirAgenda(minhaAgenda);

    // Testando remocao do ultimo
    printf("\nRemovendo a ultima missao...\n");

    if (removerUltimo(minhaAgenda, &removida)) {
        printf("Missao removida: %d - %s\n",
               removida.id, removida.descricao);
    } else {
        printf("Agenda vazia!\n");
    }

    printf("\nAgenda depois de remover o ultimo:");
    exibirAgenda(minhaAgenda);

    // Testando remocao do primeiro por ID
    printf("\nRemovendo a primeira missao pelo ID 3...\n");

    if (removerPorID(minhaAgenda, 3, &removida)) {
        printf("Missao removida: %d - %s\n",
               removida.id, removida.descricao);
    }

    exibirAgenda(minhaAgenda);

    // Testando lista com um unico elemento
    printf("\nTestando lista com um elemento...\n");

    inserirNoInicio(minhaAgenda, m1);
    exibirAgenda(minhaAgenda);

    if (removerUltimo(minhaAgenda, &removida)) {
        printf("Ultima missao removida: %d - %s\n",
               removida.id, removida.descricao);
    }

    exibirAgenda(minhaAgenda);

    // Testando lista vazia
    printf("\nTestando remocao em lista vazia...\n");

    if (!removerUltimo(minhaAgenda, &removida)) {
        printf("Nao existe missao para remover.\n");
    }

    if (!removerPorID(minhaAgenda, 99, &removida)) {
        printf("Missao de ID 99 nao encontrada.\n");
    }

    // Libera a agenda
    destruirAgenda(minhaAgenda);

    return 0;
}
