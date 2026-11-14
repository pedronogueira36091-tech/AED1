
#include <stdio.h>
#include "agenda.h"

int main() {
    Agenda* minhaAgenda = criarAgenda();

    if (minhaAgenda == NULL) {
        printf("Erro ao criar a agenda.\n");
        return 1;
    }

    // Criando missoes
    Missao m1 = {1, "Explorar a caverna principal"};
    Missao m2 = {2, "Coletar 5 ervas medicinais"};
    Missao m3 = {3, "Entregar a carta ao ferreiro"};
    Missao m4 = {4, "Encontrar o tesouro"};
    Missao m5 = {5, "Derrotar o dragao"};

    // Inserindo no inicio
    inserirNoInicio(minhaAgenda, m1);
    inserirNoInicio(minhaAgenda, m2);
    inserirNoInicio(minhaAgenda, m3);

    printf("Agenda inicial:");
    exibirAgenda(minhaAgenda);

    // Buscando a missao de ID 2
    No* referencia = buscarMissao(minhaAgenda, 2);

    if (referencia != NULL) {
        printf("\nMissao encontrada! ID: 2\n");

        if (inserirDepois(minhaAgenda, referencia, m4)) {
            printf("Nova missao inserida depois da ID 2!\n");
        }
    } else {
        printf("\nMissao de referencia nao encontrada!\n");
    }

    // Testando insercao depois do ultimo no
    No* ultima = buscarMissao(minhaAgenda, 1);

    if (ultima != NULL) {
        if (inserirDepois(minhaAgenda, ultima, m5)) {
            printf("Missao inserida depois do ultimo no!\n");
        }
    }

    // Testando uma busca que nao existe
    No* inexistente = buscarMissao(minhaAgenda, 99);

    if (inexistente == NULL) {
        printf("\nMissao de ID 99 nao encontrada. Agenda inalterada.\n");
    }

    printf("\nAgenda final:");
    exibirAgenda(minhaAgenda);

    destruirAgenda(minhaAgenda);

    return 0;
}
