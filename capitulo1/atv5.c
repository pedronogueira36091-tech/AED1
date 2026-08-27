#include <stdio.h>

//Funções das Atividades Anteriores
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
                printf("Valor fora do llimite (1 a 100)! Tente novamente.\n");
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

// --- Nova Função: Explorar com Cursor/Ponteiro Auxiliar ---
void explorar_mapa(const int *mapa, int tamanho, int *pontuacao) {
    if (!mapa || !pontuacao || tamanho <= 0) return;

    const int *ptr = mapa;               // Ponteiro auxiliar (cursor inicial)
    const int *fim = mapa + tamanho;     // Endereço limite (após o último elemento)
    int passos = 0;
    int pontos_coletados = 0;

    printf("\n=== INICIANDO EXPLORACO ===\n");

    // Avança até o endereço imediatamente posterior ao último elemento válido
    while (ptr < fim) {
        int valor = *ptr;
        pontos_coletados += valor;

        printf("Passo %d | End: %p | Valor: %d\n", passos, (void *)ptr, valor);

        passos++;
        ptr++; // Avança o cursor para o próximo elemento
    }

    // Atualiza a pontuação original do jogador
    *pontuacao += pontos_coletados;

    // Resumo do percurso
    printf("\n=== RESUMO DA EXPLORACAO ===\n");
    printf("Plataformas visitadas: %d\n", passos);
    printf("Pontos coletados no percurso: %d\n", pontos_coletados);
    printf("Pontuacao atualizada: %d\n\n", *pontuacao);
}

int main() {
    int vida = 100;
    int pontuacao = 250;
    int tamanho = 5;
    int mapa[5];

    // 1. Leitura e exibição do mapa
    ler_mapa(mapa, tamanho);
    mostrar_mapa(mapa, tamanho);

    // 2. Exploração por ponteiro auxiliar (cursor)
    explorar_mapa(mapa, tamanho, &pontuacao);

    // 3. Modificadores de estado do jogador
    printf("=== ACOES DO JOGADOR ===\n");
    aplicar_dano(&vida, 30);
    printf("Apos Dano -> Vida: %d\n", vida);

    restaurar_vida(&vida);
    printf("Apos Cura -> Vida: %d\n", vida);

    aplicar_pontuacao_dupla(&pontuacao);
    printf("Apos Bonus -> Pontuacao Final: %d\n", pontuacao);

    return 0;
}