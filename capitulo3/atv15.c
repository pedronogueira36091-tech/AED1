#include <stdio.h>

typedef struct {
    int id;
    char nome[30];
    int vida;
    int pontuacao;
    int posX;
    int posY;
} Personagem;

void ajustarVida(Personagem *p, int delta) {
    p->vida += delta;
    if (p->vida > 100)      p->vida = 100;
    else if (p->vida < 0)   p->vida = 0;
}

void ajustarPontuacao(Personagem *p, int delta) {
    p->pontuacao += delta;
    if (p->pontuacao < 0) p->pontuacao = 0;
}

void moverPersonagem(Personagem *p, int dx, int dy) {
    p->posX += dx;
    p->posY += dy;
}

void exibirEstado(const Personagem *p, const char *titulo) {
    printf("\n--- %s ---\n", titulo);
    printf("ID:        %d\n", p->id);
    printf("Nome:      %s\n", p->nome);
    printf("Vida:      %d HP\n", p->vida);
    printf("Pontuacao: %d\n", p->pontuacao);
    printf("Posicao:   (%d, %d)\n", p->posX, p->posY);
}

int main(void) {
    Personagem heroi = {0};

    printf("=== Criacao do personagem ===\n");

    printf("ID: ");
    scanf("%d", &heroi.id);

    printf("Nome: ");
    scanf(" %29[^\n]", heroi.nome);

    printf("Vida inicial (0-100): ");
    scanf("%d", &heroi.vida);
    ajustarVida(&heroi, 0);

    printf("Pontuacao inicial: ");
    scanf("%d", &heroi.pontuacao);
    ajustarPontuacao(&heroi, 0);

    printf("Posicao X: ");
    scanf("%d", &heroi.posX);

    printf("Posicao Y: ");
    scanf("%d", &heroi.posY);

    exibirEstado(&heroi, "Estado inicial");

    int deltaVida, deltaPontuacao, dx, dy;

    printf("Quanto de vida ganhar/perder (ex: -30): ");
    scanf("%d", &deltaVida);
    ajustarVida(&heroi, deltaVida);

    printf("Quanto de pontuacao ganhar/perder (ex: 50): ");
    scanf("%d", &deltaPontuacao);
    ajustarPontuacao(&heroi, deltaPontuacao);

    printf("Deslocamento X e Y (ex: 5 -2): ");
    scanf("%d %d", &dx, &dy);
    moverPersonagem(&heroi, dx, dy);

    exibirEstado(&heroi, "Estado apos alteracoes");

    return 0;
}