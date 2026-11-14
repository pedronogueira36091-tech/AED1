
#include <stdio.h>
#include "agenda.h"

int main() {
    // Cria a agenda
    Agenda* minhaAgenda = criarAgenda();

    if (minhaAgenda == NULL) {
        printf("Erro ao criar agenda.\n");
        return 1;
    }

    // Verifica o tamanho inicial
    printf("Tamanho inicial da agenda: %d\n",
           tamanhoAgenda(minhaAgenda));

    // Criando missoes iniciais
    Missao m1 = {1, "Explorar a caverna"};
    Missao m2 = {2, "Coletar ervas"};
    Missao m3 = {3, "Entregar a carta"};

    // Inserindo missoes iniciais
    inserirNoInicio(minhaAgenda, m1);
    inserirNoInicio(minhaAgenda, m2);
    inserirNoInicio(minhaAgenda, m3);

    printf("\nAgenda antes da importacao:");
    exibirAgenda(minhaAgenda);

    printf("\nTamanho antes da importacao: %d\n",
           tamanhoAgenda(minhaAgenda));

    // Criando um lote de missoes
    Missao lote[] = {
        {4, "Encontrar o tesouro"},
        {5, "Derrotar o dragao"},
        {6, "Salvar a princesa"}
    };

    int quantidade = sizeof(lote) / sizeof(lote[0]);

    // Inserindo o lote na agenda
    printf("\nImportando missoes em lote...\n");

    if (inserirLote(minhaAgenda, lote, quantidade)) {
        printf("Lote importado com sucesso!\n");
    } else {
        printf("Erro ao importar o lote.\n");
    }

    // Mostra o tamanho depois da importacao
    printf("\nTamanho depois da importacao: %d\n",
           tamanhoAgenda(minhaAgenda));

    printf("\nAgenda depois da importacao:");
    exibirAgenda(minhaAgenda);

    // Testando lote vazio
    printf("\nTestando lote vazio...\n");

    if (inserirLote(minhaAgenda, lote, 0)) {
        printf("Nenhuma missao adicionada. Operacao valida.\n");
    }

    printf("Tamanho atual: %d\n",
           tamanhoAgenda(minhaAgenda));

    // Testando quantidade invalida
    printf("\nTestando quantidade negativa...\n");

    if (!inserirLote(minhaAgenda, lote, -1)) {
        printf("Quantidade invalida. Operacao cancelada.\n");
    }

    // Testando limpeza da agenda
    printf("\nLimpando a agenda...\n");

    limparAgenda(minhaAgenda);

    printf("Tamanho depois da limpeza: %d\n",
           tamanhoAgenda(minhaAgenda));

    exibirAgenda(minhaAgenda);

    // Libera a memoria
    destruirAgenda(minhaAgenda);

    printf("\nPrograma encerrado.\n");

    return 0;
}
