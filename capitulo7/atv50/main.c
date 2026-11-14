
#include <stdio.h>
#include "agenda.h"

int main() {
    // Cria a agenda
    Agenda* minhaAgenda = criarAgenda();

    if (minhaAgenda == NULL) {
        printf("Erro ao criar agenda.\n");
        return 1;
    }

    // Criando missoes com suas prioridades
    Missao m1 = {1, "Explorar a caverna", 3};
    Missao m2 = {2, "Coletar ervas", 5};
    Missao m3 = {3, "Entregar a carta", 8};
    Missao m4 = {4, "Derrotar o dragao", 10};
    Missao m5 = {5, "Encontrar o tesouro", 5};

    // Inserindo missoes
    inserirNoInicio(minhaAgenda, m1);
    inserirNoInicio(minhaAgenda, m2);
    inserirNoInicio(minhaAgenda, m3);
    inserirNoInicio(minhaAgenda, m4);
    inserirNoInicio(minhaAgenda, m5);

    printf("\nAgenda antes da ordenacao:");
    exibirAgenda(minhaAgenda);

    // Mostra a quantidade de missoes
    printf("\nQuantidade de missoes: %d\n",
           tamanhoAgenda(minhaAgenda));

    // Ordena por prioridade
    printf("\nOrdenando as missoes por prioridade...\n");

    ordenarAgenda(minhaAgenda);

    printf("\nAgenda depois da ordenacao:");
    exibirAgenda(minhaAgenda);

    // Salva a agenda no arquivo
    printf("\nSalvando missoes no arquivo...\n");

    if (salvarAgenda(minhaAgenda, "missoes.dat")) {
        printf("Missoes salvas com sucesso!\n");
    } else {
        printf("Erro ao salvar as missoes.\n");
        destruirAgenda(minhaAgenda);
        return 1;
    }

    // Limpa a agenda para testar a leitura
    printf("\nLimpando a agenda para testar a leitura...\n");

    limparAgenda(minhaAgenda);

    printf("Quantidade depois da limpeza: %d\n",
           tamanhoAgenda(minhaAgenda));

    // Carrega as missoes salvas
    printf("\nCarregando missoes do arquivo...\n");

    if (carregarAgenda(minhaAgenda, "missoes.dat")) {
        printf("Missoes carregadas com sucesso!\n");
    } else {
        printf("Erro ao carregar as missoes.\n");
    }

    // Exibe os dados recuperados
    printf("\nAgenda recuperada do arquivo:");
    exibirAgenda(minhaAgenda);

    printf("\nQuantidade depois da leitura: %d\n",
           tamanhoAgenda(minhaAgenda));

    // Libera a memoria
    destruirAgenda(minhaAgenda);

    printf("\nPrograma encerrado!\n");

    return 0;
}
