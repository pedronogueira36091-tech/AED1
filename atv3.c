#include <stdio.h>

// --- Funções das Atividades Anteriores ---
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

int main() {
    int vida = 100;
    int pontuacao = 250;

    // --- Atividade Atual: Vetor e Aritmética de Ponteiros ---
    // Cada elemento representa o impulso/pontos de uma plataforma
    int plataformas[5] = {10, 25, 5, 50, 15};
    int soma_pontos = 0;

    printf("=== EXPLORANDO AS PLATAFORMAS ===\n");
    for (int i = 0; i < 5; i++) {
        int valor = *(plataformas + i);
        int *endereco = plataformas + i;

        soma_pontos += valor;

        printf("Plataforma %d -> End: %p | Impulso/Pontos: %d\n", 
               i, (void *)endereco, valor);
    }

    // Atualiza a pontuação total do jogador com os pontos do percurso
    pontuacao += soma_pontos;

    printf("\nTotal coletado nas plataformas: %d\n", soma_pontos);
    printf("Pontuacao atual do jogador: %d\n\n", pontuacao);

    // --- Teste das Funções Anteriores ---
    printf("=== ACOES DO JOGADOR ===\n");
    aplicar_dano(&vida, 30);
    printf("Apos Dano -> Vida: %d\n", vida);

    restaurar_vida(&vida);
    printf("Apos Cura -> Vida: %d\n", vida);

    aplicar_pontuacao_dupla(&pontuacao);
    printf("Apos Bonus -> Pontuacao Final: %d\n", pontuacao);

    return 0;
}