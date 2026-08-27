#include <stdio.h>

// Funções das Atividades Anteriores
void aplicar_dano(int *vida, int dano) {
    if (!vida) return;
    *vida = *vida - dano;
}

void restaurar_vida(int *vida) {
    if (!vida) return;
    *vida = *vida + 15;
}

void aplicar_pontuacao_dupla(int *pontuacao) {
    if (!pontuacao) return;
    *pontuacao = *pontuacao * 2;
}

// Novas Funções 

// Lê os valores das plataformas via teclado usando aritmética de ponteiros
void ler_mapa(int *mapa, int tamanho) {
    if (!mapa || tamanho <= 0 || tamanho > 10) {
        printf("Tamanho invalido!\n");
        return;
    }

    printf("--- DIGITE OS VALORES DAS %d PLATAFORMAS (1 a 100) ---\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        int valor;
        do {
            printf("Plataforma %d: ", i);
            scanf("%d", &valor);
            if (valor < 1 || valor > 100) {
                printf("Valor fora do limite (1 a 100)! Tente novamente.\n");
            }
        } while (valor < 1 || valor > 100);

        *(mapa + i) = valor;
    } 
}

void mostrar_mapa(const int *mapa, int tamanho) {
    if (!mapa || tamanho <= 0) return;

    printf("\n=== MAPA DA FASE ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Plataforma %d -> End: %p | Valor: %d\n", 
               i, (void *)(mapa + i), *(mapa + i));
    }
}

int main() {
    int vida = 100;
    int pontuacao = 250;
    int tamanho = 5;
    int mapa[5]; // Vetor para guardar o mapa configurado pelo usuário

    // 1. Leitura e exibição do mapa dinâmico
    ler_mapa(mapa, tamanho);
    mostrar_mapa(mapa, tamanho);

    // 2. Exploração do mapa e acúmulo de pontos
    int soma_pontos = 0;
    for (int i = 0; i < tamanho; i++) {
        soma_pontos += *(mapa + i);
    }
    pontuacao += soma_pontos;

    printf("\nTotal coletado no mapa: %d\n", soma_pontos);
    printf("Pontuacao atual do jogador: %d\n\n", pontuacao);

    // 3. Teste das funções de estado do jogador
    printf("=== ACOES DO JOGADOR ===\n");
    aplicar_dano(&vida, 30);
    printf("Apos Dano -> Vida: %d\n", vida);

    restaurar_vida(&vida);
    printf("Apos Cura -> Vida: %d\n", vida);

    aplicar_pontuacao_dupla(&pontuacao);
    printf("Apos Bonus -> Pontuacao Final: %d\n", pontuacao);

    return 0;
}