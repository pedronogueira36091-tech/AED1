#include <stdio.h>

// --- Funções de Estado do Jogador ---
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

// --- Funções do Mapa ---
void ler_mapa(int *mapa, int tamanho) {
    if (!mapa || tamanho <= 0 || tamanho > 10) return;

    printf("\n--- DIGITE OS VALORES DAS %d PLATAFORMAS (1 a 100) ---\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        int valor;
        do {
            printf("Plataforma %d: ", i);
            scanf("%d", &valor);
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

void explorar_mapa(const int *mapa, int tamanho, int *pontuacao) {
    if (!mapa || !pontuacao || tamanho <= 0) return;

    const int *ptr = mapa;
    const int *fim = mapa + tamanho;
    int passos = 0, pontos_coletados = 0;

    printf("\n=== EXPLORANDO MAPA ===\n");
    while (ptr < fim) {
        pontos_coletados += *ptr;
        printf("Passo %d | End: %p | Valor: %d\n", passos, (void *)ptr, *ptr);
        passos++;
        ptr++;
    }

    *pontuacao += pontos_coletados;
    printf("\nResumo: %d plataformas exploradas | Pontos ganhos: %d\n", passos, pontos_coletados);
}


void mostrar_inventario_vetor(int *inventario[], int qtd) {
    if (!inventario) return;
    printf("\n=== INVENTARIO (Via Notacao de Vetor inventario[i]) ===\n");
    for (int i = 0; i < qtd; i++) {
        if (inventario[i] != NULL) {
            printf("Item %d -> Aponta para: %p | Valor guardado: %d\n", 
                   i, (void *)inventario[i], *inventario[i]);
        }
    }
}

void mostrar_inventario_ponteiro(int **inventario, int qtd) {
    if (!inventario) return;
    printf("\n=== INVENTARIO (Via Aritmetica *(inventario + i)) ===\n");
    for (int i = 0; i < qtd; i++) {
        int *ptr_item = *(inventario + i);
        if (ptr_item != NULL) {
            printf("Item %d -> Aponta para: %p | Valor guardado: %d\n", 
                   i, (void *)ptr_item, *ptr_item);
        }
    }
}

// Alteração de um item usando vetor de ponteiros
void alterar_item_inventario(int *inventario[], int qtd, int indice, int novo_valor) {
    if (!inventario || indice < 0 || indice >= qtd) {
        printf("Indice invalido!\n");
        return;
    }
    // Modifica diretamente a variável original referenciada pelo ponteiro
    *inventario[indice] = novo_valor;
    printf("Item %d alterado para %d com sucesso!\n", indice, novo_valor);
}

// --- Menu e Execução Principal ---
int main() {
    int vida = 100;
    int pontuacao = 250;
    int tamanho_mapa = 5;
    int mapa[5] = {10, 20, 30, 40, 50};

    // 1. Três itens independentes no estado do jogo
    int pocao_cura = 50;
    int moedas_ouro = 100;
    int escudo_defesa = 25;

    // 2. Vetor de ponteiros (Guarda referências/endereços para os 3 itens)
    int *inventario[3];
    inventario[0] = &pocao_cura;
    inventario[1] = &moedas_ouro;
    inventario[2] = &escudo_defesa;

    int opcao;

    do {
        printf("\n================ MENU DO SIMULADOR ================\n");
        printf("Estado Atual -> Vida: %d | Pontos: %d\n", vida, pontuacao);
        printf("1. Aplicar Dano (-30)\n");
        printf("2. Restaurar Vida (+15)\n");
        printf("3. Aplicar Pontuacao Dupla (x2)\n");
        printf("4. Configurar e Mostrar Mapa\n");
        printf("5. Explorar Mapa\n");
        printf("6. Consultar Inventario (Notacao de Vetor)\n");
        printf("7. Consultar Inventario (Aritmetica de Ponteiros)\n");
        printf("8. Alterar Valor de um Item no Inventario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                aplicar_dano(&vida, 30);
                printf("Dano aplicado! Nova vida: %d\n", vida);
                break;
            case 2:
                restaurar_vida(&vida);
                printf("Vida restaurada! Nova vida: %d\n", vida);
                break;
            case 3:
                aplicar_pontuacao_dupla(&pontuacao);
                printf("Bônus aplicado! Nova pontuacao: %d\n", pontuacao);
                break;
            case 4:
                ler_mapa(mapa, tamanho_mapa);
                mostrar_mapa(mapa, tamanho_mapa);
                break;
            case 5:
                explorar_mapa(mapa, tamanho_mapa, &pontuacao);
                break;
            case 6:
                mostrar_inventario_vetor(inventario, 3);
                break;
            case 7:
                mostrar_inventario_ponteiro(inventario, 3);
                break;
            case 8: {
                int idx, val;
                printf("Qual item deseja alterar (0 a 2)? ");
                scanf("%d", &idx);
                printf("Digite o novo valor: ");
                scanf("%d", &val);
                alterar_item_inventario(inventario, 3, idx, val);
                break;
            }
            case 0:
                printf("Saindo do simulador...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}