#include <stdio.h>

typedef struct {
    int id;
    char jogador[30];
    int pontuacao;
} Partida;

void processar_relatorio(const char *origem, const char *destino) {
    FILE *arq_origem = fopen(origem, "r");
    if (arq_origem == NULL) {
        printf("Erro ao abrir arquivo de origem.\n");
        return;
    }

    FILE *arq_destino = fopen(destino, "w");
    if (arq_destino == NULL) {
        printf("Erro ao criar arquivo de destino.\n");
        fclose(arq_origem);
        return;
    }

    Partida p;
    int processados = 0;

    while (fscanf(arq_origem, "%d %29s %d", &p.id, p.jogador, &p.pontuacao) == 3) {
        int bonus = p.pontuacao * 0.10;
        int pontuacao_final = p.pontuacao + bonus;

        fprintf(arq_destino, "%d %s %d\n", p.id, p.jogador, pontuacao_final);
        processados++;
    }

    fclose(arq_origem);
    fclose(arq_destino);

    printf("Registros processados: %d\n", processados);
}

int main() {
    processar_relatorio("resultados_brutos.txt", "relatorio_final.txt");
    return 0;
}