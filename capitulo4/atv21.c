#include <stdio.h>

typedef struct {
    int id;
    char jogador[30];
    int pontuacao;
} Partida;

void salvar_partida(const char *nome_arquivo, Partida p) {
    FILE *arq = fopen(nome_arquivo, "w");
    if (arq == NULL) return;

    fprintf(arq, "%d %s %d\n", p.id, p.jogador, p.pontuacao);
    fclose(arq);
}

void ler_partidas(const char *nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL) return;

    Partida p;
    while (fscanf(arq, "%d %29s %d", &p.id, p.jogador, &p.pontuacao) == 3) {
        printf("%d %s %d\n", p.id, p.jogador, p.pontuacao);
    }

    fclose(arq);
}

int main() {
    Partida p = {1, "Jogador1", 1500};

    salvar_partida("relatorio.txt", p);
    ler_partidas("relatorio.txt");

    return 0;
}