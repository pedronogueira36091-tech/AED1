#include <stdio.h>

typedef struct {
    int id;
    char jogador[30];
    int pontuacao;
} Partida;

void salvar_binario(const char *nome_arquivo, Partida p) {
    FILE *arq = fopen(nome_arquivo, "wb");
    if (arq == NULL) return;

    size_t escritos = fwrite(&p, sizeof(Partida), 1, arq);
    if (escritos != 1) {
        printf("Erro ao gravar registro.\n");
    }

    fclose(arq);
}

void ler_binario(const char *nome_arquivo, Partida p_original) {
    FILE *arq = fopen(nome_arquivo, "rb");
    if (arq == NULL) {
        printf("Arquivo vazio ou inexistente.\n");
        return;
    }

    Partida p_lida;
    size_t lidos = fread(&p_lida, sizeof(Partida), 1, arq);

    if (lidos == 0) {
        printf("Arquivo vazio ou registro incompleto.\n");
    } else if (lidos == 1) {
        printf("Objeto reconstruido:\n");
        printf("ID: %d | Jogador: %s | Pontos: %d\n", p_lida.id, p_lida.jogador, p_lida.pontuacao);

        if (p_lida.id == p_original.id && p_lida.pontuacao == p_original.pontuacao) {
            printf("Registro restaurado perfeitamente.\n");
        }
    }

    fclose(arq);
}

int main() {
    Partida p_original = {1, "Jogador1", 2500};

    salvar_binario("partida.bin", p_original);
    ler_binario("partida.bin", p_original);

    return 0;
}