#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// pegar nome de jogador
typedef struct {
    char nome[50];
    int idade;
} Jogador;

int main() {
    int quantidade;

    printf("Digite a quantidade de jogadores da equipe: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida! O numero deve ser maior que zero.\n");
        return 1;
    }

    Jogador *equipe = (Jogador *) malloc(quantidade * sizeof(*equipe));

    if (equipe == NULL) {
        printf("Erro ao alocar memoria! Operacao encerrada.\n");
        return 1; // Encerra sem acessar o ponteiro
    }

    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Jogador %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", equipe[i].nome); 
        printf("Idade: ");
        scanf("%d", &equipe[i].idade);
    }

    printf("\n=== JOGGADORES CADASTRADOS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Jogador %d: %s, %d anos\n", i + 1, equipe[i].nome, equipe[i].idade);
    }

    free(equipe);
    equipe = NULL;

    return 0;
}