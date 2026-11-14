
#include <stdio.h>
#include <string.h>
#include "agenda.h"

int main() {
    Agenda* minhaAgenda = criarAgenda();

    if (minhaAgenda == NULL) {
        printf("Erro ao criar agenda.\n");
        return 1;
    }

    // Carrega automaticamente ao iniciar
    printf("Carregando agenda...\n");

    if (carregarAgenda(minhaAgenda, "missoes.dat")) {
        printf("Carregamento concluido.\n");
    } else {
        printf("Nao foi possivel carregar o arquivo.\n");
    }

    int opcao;

    do {
        printf("\n===== AGENDA DE MISSOES =====\n");
        printf("1 - Exibir missoes\n");
        printf("2 - Inserir missao\n");
        printf("3 - Ordenar por prioridade\n");
        printf("4 - Salvar agenda\n");
        printf("5 - Carregar agenda\n");
        printf("6 - Mostrar quantidade\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            opcao = -1;
            continue;
        }

        switch (opcao) {

            case 1:
                exibirAgenda(minhaAgenda);
                break;

            case 2: {
                Missao m;

                printf("Digite o ID: ");
                if (scanf("%d", &m.id) != 1) {
                    printf("ID invalido!\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }

                if (m.id <= 0 || buscarMissao(minhaAgenda, m.id) != NULL) {
                    printf("ID invalido ou ja existente!\n");
                    break;
                }

                getchar();

                printf("Digite a descricao: ");

                if (fgets(m.descricao, sizeof(m.descricao), stdin) == NULL) {
                    printf("Erro ao ler descricao.\n");
                    break;
                }

                m.descricao[strcspn(m.descricao, "\n")] = '\0';

                if (m.descricao[0] == '\0') {
                    printf("Descricao nao pode ser vazia.\n");
                    break;
                }

                printf("Digite a prioridade (1 a 10): ");

                if (scanf("%d", &m.prioridade) != 1) {
                    printf("Prioridade invalida!\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }

                if (m.prioridade < 1 || m.prioridade > 10) {
                    printf("Prioridade deve ser de 1 a 10.\n");
                    break;
                }

                if (inserirNoInicio(minhaAgenda, m)) {
                    printf("Missao inserida com sucesso!\n");
                } else {
                    printf("Erro ao inserir missao.\n");
                }

                break;
            }

            case 3:
                ordenarAgenda(minhaAgenda);
                printf("Agenda ordenada por prioridade!\n");
                exibirAgenda(minhaAgenda);
                break;

            case 4:
                if (salvarAgenda(minhaAgenda, "missoes.dat")) {
                    printf("Agenda salva com sucesso!\n");
                } else {
                    printf("Erro ao salvar agenda.\n");
                }
                break;

            case 5:
                if (carregarAgenda(minhaAgenda, "missoes.dat")) {
                    printf("Agenda carregada com sucesso!\n");
                    exibirAgenda(minhaAgenda);
                } else {
                    printf("Falha ao carregar agenda.\n");
                }
                break;

            case 6:
                printf("Quantidade de missoes: %d\n",
                       tamanhoAgenda(minhaAgenda));
                break;

            case 0:
                // Salva antes de encerrar
                if (salvarAgenda(minhaAgenda, "missoes.dat")) {
                    printf("Agenda salva antes de sair.\n");
                } else {
                    printf("Aviso: nao foi possivel salvar a agenda.\n");
                }

                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    destruirAgenda(minhaAgenda);

    printf("Memoria liberada. Programa encerrado!\n");

    return 0;
}
