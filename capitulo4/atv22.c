#include <stdio.h>

typedef struct {
    int id;
    char jogador[30];
    int pontuacao;
} Partida;

void adicionar_partida(const char *nome_arquivo, Partida p) {
    FILE *arq = fopen(nome_arquivo, "a");
    if (arq == NULL) return;

    fprintf(arq, "%d %s %d\n", p.id, p.jogador, p.pontuacao);
    fclose(arq);
}

void listar_historico(const char *nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "r");
    if (arq == NULL) {
        printf("Historico vazio.\n");
        return;
    }

    Partida p;
    int res;
    int total = 0;

    while ((res = fscanf(arq, "%d %29s %d", &p.id, p.jogador, &p.pontuacao)) == 3) {
        printf("%d %s %d\n", p.id, p.jogador, p.pontuacao);
        total++;
    }

    if (res != EOF && res != 3) {
        printf("Dado malformado encontrado.\n");
    }

    if (total == 0) {
        printf("Historico vazio.\n");
    } else {
        printf("Total de registros: %d\n", total);
    }

    fclose(arq);
}

int main() {
    Partida p1 = {1, "Jogador1", 100};
    Partida p2 = {2, "Jogador2", 200};

    adicionar_partida("historico.txt", p1);
    adicionar_partida("historico.txt", p2);

    listar_historico("historico.txt");

    return 0;
}