
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
    Missao m6 = {6, "Salvar a princesa"};

    // Inserindo no inicio
    inserirNoInicio(minhaAgenda, m1);
    inserirNoInicio(minhaAgenda, m2);
    inserirNoInicio(minhaAgenda, m3);

    printf("\nAgenda inicial:");
    exibirAgenda(minhaAgenda);

    // Atividade anterior: inserir depois do ID 2
    No* referencia = buscarMissao(minhaAgenda, 2);

    if (referencia != NULL) {
        inserirDepois(minhaAgenda, referencia, m4);
    }

    // NOVA ATIVIDADE: inserir antes do ID 3
    printf("\nInserindo antes da missao ID 3...\n");

    if (inserirAntes(minhaAgenda, 3, m5)) {
        printf("Missao inserida com sucesso!\n");
    } else {
        printf("Missao de referencia nao encontrada!\n");
    }

    exibirAgenda(minhaAgenda);

    // Testando insercao antes do primeiro no
    printf("\nInserindo antes do primeiro no...\n");

    if (inserirAntes(minhaAgenda, 3, m6)) {
        printf("Missao inserida no inicio com sucesso!\n");
    }

    exibirAgenda(minhaAgenda);

    // NOVA ATIVIDADE: remover o primeiro no
    printf("\nRemovendo a primeira missao...\n");

    Missao removida;

    if (removerPrimeiro(minhaAgenda, &removida)) {
        printf("Missao removida:\n");
        printf("ID: %d\n", removida.id);
        printf("Descricao: %s\n", removida.descricao);
    } else {
        printf("Nao foi possivel remover. Agenda vazia!\n");
    }

    printf("\nAgenda depois da remocao:");
    exibirAgenda(minhaAgenda);

    // Testando referencia inexistente
    printf("\nTentando inserir antes do ID 99...\n");

    if (!inserirAntes(minhaAgenda, 99, m6)) {
        printf("ID nao encontrado. Agenda permanece inalterada.\n");
    }

    // Libera a memória
    destruirAgenda(minhaAgenda);

    return 0;
}
