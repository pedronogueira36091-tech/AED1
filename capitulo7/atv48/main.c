
#include <stdio.h>
#include "agenda.h"

int main() {
    // Cria a agenda
    Agenda* minhaAgenda = criarAgenda();

    if (minhaAgenda == NULL) {
        printf("Erro ao criar agenda.\n");
        return 1;
    }

    // Criando missoes
    Missao m1 = {1, "Explorar a caverna"};
    Missao m2 = {2, "Coletar ervas"};
    Missao m3 = {3, "Entregar a carta"};

    // Inserindo missoes
    inserirNoInicio(minhaAgenda, m1);
    inserirNoInicio(minhaAgenda, m2);
    inserirNoInicio(minhaAgenda, m3);

    printf("\nAgenda inicial:");
    exibirAgenda(minhaAgenda);

    // Testando alteracao de missao
    printf("\nAlterando a missao de ID 2...\n");

    if (alterarMissao(minhaAgenda, 2,
                      "Coletar 10 ervas medicinais")) {
        printf("Missao alterada com sucesso!\n");
    } else {
        printf("Nao foi possivel alterar a missao.\n");
    }

    printf("\nAgenda depois da alteracao:");
    exibirAgenda(minhaAgenda);

    // Testando alteracao de ID inexistente
    printf("\nTentando alterar o ID 99...\n");

    if (!alterarMissao(minhaAgenda, 99,
                       "Nova descricao")) {
        printf("Missao nao encontrada!\n");
    }

    // Testando descricao vazia
    printf("\nTestando descricao vazia...\n");

    if (!alterarMissao(minhaAgenda, 2, "")) {
        printf("Descricao invalida. Alteracao cancelada.\n");
    }

    // Limpando toda a agenda
    printf("\nLimpando toda a agenda...\n");

    limparAgenda(minhaAgenda);

    exibirAgenda(minhaAgenda);

    // Testando limpeza de lista ja vazia
    printf("\nTentando limpar novamente...\n");

    limparAgenda(minhaAgenda);

    printf("Limpeza realizada sem erros.\n");

    // Testando se a agenda pode ser reutilizada
    printf("\nInserindo nova missao depois da limpeza...\n");

    inserirNoInicio(minhaAgenda, m1);

    exibirAgenda(minhaAgenda);

    // Destroi a agenda e libera toda a memoria
    printf("\nEncerrando o programa...\n");

    destruirAgenda(minhaAgenda);

    printf("Agenda destruida e memoria liberada!\n");

    return 0;
}
