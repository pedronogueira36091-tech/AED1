#include <stdio.h>

int main() {
    int vida = 100;
    int tesouro = 0; // 0 = inativo, 1 = ativo
    int *pVida = &vida;
    int *pTesouro = &tesouro;

    // Estado Inicial
    printf("Inicial -> Vida: %d  | Tesouro: %d \n", *pVida,  *pTesouro);

    // Dano (-30) via ponteiro
    *pVida = *pVida - 30;
    printf("Apos Dano -> Vida: %d\n", vida);

    // Cura (+15) via ponteiro
    *pVida = *pVida + 15;
    printf("Apos Cura -> Vida: %d\n", vida);

    // Ativar tesouro via ponteiro
    *pTesouro = 1;
    printf("Apos Tesouro -> Tesouro: %d\n", tesouro);

    return 0;
}