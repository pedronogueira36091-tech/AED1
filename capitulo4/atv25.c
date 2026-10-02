#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char jogador[30];
    int pontuacao;
} Partida;

typedef struct {
    Partida *vetor;
    int qtd;
} Temporada;

void cadastrar(Temporada *temp) {
    Partida *novo_vetor = (Partida *)realloc(temp->vetor, (temp->qtd + 1) * sizeof(Partida));
    if (novo_vetor == NULL) return;

    temp->vetor = novo_vetor;
    Partida *p = &temp->vetor[temp->qtd];
    p->id = temp->qtd + 1;

    int i = 0;
    char c;
    getchar();
    while (i < 29) {
        c = getchar();
        if (c == '\n' || c == EOF) break;
        p->jogador[i++] = c;
    }
    p->jogador[i] = '\0';

    scanf("%d", &p->pontuacao);
    temp->qtd++;
}

void listar(Temporada *temp) {
    for (int i = 0; i < temp->qtd; i++) {
        printf("ID: %d | Jogador: %s | Pontos: %d\n",
               temp->vetor[i].id, temp->vetor[i].jogador, temp->vetor[i].pontuacao);
    }
}

void salvar(const char *nome_arquivo, Temporada *temp) {
    FILE *arq = fopen(nome_arquivo, "wb");
    if (arq == NULL) return;

    if (fwrite(&temp->qtd, sizeof(int), 1, arq) != 1) {
        fclose(arq);
        return;
    }

    if (temp->qtd > 0) {
        if (fwrite(temp->vetor, sizeof(Partida), temp->qtd, arq) != (size_t)temp->qtd) {
            fclose(arq);
            return;
        }
    }

    fclose(arq);
}

void carregar(const char *nome_arquivo, Temporada *temp) {
    FILE *arq = fopen(nome_arquivo, "rb");
    if (arq == NULL) return;

    int nova_qtd;
    if (fread(&nova_qtd, sizeof(int), 1, arq) != 1 || nova_qtd <= 0) {
        fclose(arq);
        return;
    }

    Partida *temp_vetor = (Partida *)malloc(nova_qtd * sizeof(Partida));
    if (temp_vetor == NULL) {
        fclose(arq);
        return;
    }

    if (fread(temp_vetor, sizeof(Partida), nova_qtd, arq) != (size_t)nova_qtd) {
        free(temp_vetor);
        fclose(arq);
        return;
    }

    fclose(arq);

    free(temp->vetor);
    temp->vetor = temp_vetor;
    temp->qtd = nova_qtd;
}

int main() {
    Temporada temp = {NULL, 0};
    int opcao;

    do {
        scanf("%d", &opcao);
        if (opcao == 1) {
            cadastrar(&temp);
        } else if (opcao == 2) {
            listar(&temp);
        } else if (opcao == 3) {
            salvar("temporada.bin", &temp);
        } else if (opcao == 4) {
            carregar("temporada.bin", &temp);
        }
    } while (opcao != 0);

    free(temp.vetor);
    return 0;
}