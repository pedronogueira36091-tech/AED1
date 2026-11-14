
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

    // Remover depois do ID 3
    printf("\nRemovendo depois do ID 3...\n");

    if (removerDepois(minhaAgenda, 3, &removida)) {
        printf("Missao removida: %d - %s\n",
               removida.id, removida.descricao);
    } else {
        printf("Nao existe missao depois dessa referencia.\n");
    }

    exibirAgenda(minhaAgenda);

    // Remover antes do ID 3
    printf("\nRemovendo antes do ID 3...\n");

    if (removerAntes(minhaAgenda, 3, &removida)) {
        printf("Missao removida: %d - %s\n",
               removida.id, removida.descricao);
    } else {
        printf("Nao existe missao antes dessa referencia.\n");
    }

    exibirAgenda(minhaAgenda);

    // Testando referencia inexistente
    printf("\nTestando ID inexistente...\n");

    if (!removerAntes(minhaAgenda, 99, &removida)) {
        printf("Referencia nao encontrada.\n");
    }

    // Testando remocao antes do primeiro
    printf("\nTestando remocao antes do primeiro...\n");

    if (!removerAntes(minhaAgenda, 4, &removida)) {
        printf("Nao existe missao antes do primeiro no.\n");
    }

    // Testando remocao depois do ultimo
    printf("\nTestando remocao depois do ultimo...\n");

    if (!removerDepois(minhaAgenda, 1, &removida)) {
        printf("Nao existe missao depois do ultimo no.\n");
    }

    printf("\nAgenda final:");
    exibirAgenda(minhaAgenda);

    destruirAgenda(minhaAgenda);

    return 0;
}
