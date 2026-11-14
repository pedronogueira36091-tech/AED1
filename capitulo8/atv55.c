
#include <stdio.h>
#include <stdlib.h>

// Dados da acao
typedef struct {
    int codigo;
    char descricao[100];
} Acao;

// No da pilha
typedef struct No {
    Acao dados;
    struct No *prox;
} No;

// Estrutura da pilha
typedef struct {
    No *topo;
} Pilha;

// Dados do jogador
typedef struct {
    int codigo;
    char nome[100];
} Jogador;

// No da fila
typedef struct NoFila {
    Jogador dados;
    struct NoFila *prox;
} NoFila;

// Estrutura da fila
typedef struct {
    NoFila *inicio;
    NoFila *fim;
} Fila;

// Copiar texto sem usar string.h
void copiarTexto(char destino[], char origem[]) {
    int i = 0;

    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }

    destino[i] = '\0';
}

// =====================================
// OPERACOES DA PILHA
// =====================================

// Inicializar a pilha
void inicializar(Pilha *p) {
    p->topo = NULL;
}

// Verificar se a pilha esta vazia
int esta_vazia(Pilha *p) {
    return p->topo == NULL;
}

// Inserir elemento (PUSH)
int push(Pilha *p, Acao a) {
    No *novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 0;
    }

    novo->dados = a;
    novo->prox = p->topo;
    p->topo = novo;

    return 1;
}

// Consultar o topo (PEEK)
int peek(Pilha *p, Acao *consulta) {
    if (esta_vazia(p)) {
        return 0;
    }

    *consulta = p->topo->dados;

    return 1;
}

// Exibir a pilha
void exibir(Pilha *p) {
    No *aux = p->topo;

    if (esta_vazia(p)) {
        printf("Pilha vazia!\n");
        return;
    }

    printf("\n--- Historico de acoes ---\n");

    while (aux != NULL) {
        printf("Codigo: %d | Acao: %s\n",
               aux->dados.codigo,
               aux->dados.descricao);

        aux = aux->prox;
    }
}

// Remover elemento (POP)
int pop(Pilha *p, Acao *removida) {
    if (esta_vazia(p)) {
        return 0;
    }

    No *aux = p->topo;

    *removida = aux->dados;
    p->topo = aux->prox;

    free(aux);

    return 1;
}

// Inverter a pilha
void inverter(Pilha *p) {
    No *anterior = NULL;
    No *atual = p->topo;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    p->topo = anterior;
}

// Limpar a pilha
void limpar(Pilha *p) {
    Acao removida;

    while (pop(p, &removida));
}

// Salvar a pilha
int salvar(Pilha *p) {
    FILE *arquivo = fopen("acoes.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 0;
    }

    No *aux = p->topo;

    while (aux != NULL) {
        if (fwrite(&aux->dados, sizeof(Acao), 1, arquivo) != 1) {
            fclose(arquivo);
            printf("Erro ao gravar dados!\n");
            return 0;
        }

        aux = aux->prox;
    }

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar arquivo!\n");
        return 0;
    }

    printf("Pilha salva com sucesso!\n");

    return 1;
}

// Carregar a pilha
int carregar(Pilha *p) {
    FILE *arquivo;
    Acao a;
    size_t lidos;

    limpar(p);

    arquivo = fopen("acoes.dat", "rb");

    if (arquivo == NULL) {
        printf("Arquivo nao encontrado. Pilha vazia!\n");
        return 0;
    }

    while ((lidos = fread(&a, 1, sizeof(Acao), arquivo)) ==
           sizeof(Acao)) {

        if (!push(p, a)) {
            fclose(arquivo);
            limpar(p);
            return 0;
        }
    }

    if (lidos != 0 || ferror(arquivo)) {
        fclose(arquivo);
        limpar(p);
        printf("Erro na leitura do arquivo!\n");
        return 0;
    }

    if (fclose(arquivo) != 0) {
        limpar(p);
        printf("Erro ao fechar arquivo!\n");
        return 0;
    }

    inverter(p);

    printf("Pilha carregada com sucesso!\n");

    return 1;
}

// =====================================
// OPERACOES DA FILA
// =====================================

// Inicializar a fila
void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Verificar se a fila esta vazia
int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

// Inserir jogador no final da fila
int enfileirar(Fila *f, Jogador j) {
    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));

    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 0;
    }

    novo->dados = j;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }

    return 1;
}

// Exibir jogadores do inicio ao fim
void exibirFila(Fila *f) {
    NoFila *aux = f->inicio;

    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("\n--- Fila de jogadores ---\n");

    while (aux != NULL) {
        printf("Codigo: %d | Jogador: %s\n",
               aux->dados.codigo,
               aux->dados.nome);

        aux = aux->prox;
    }
}

// Remover jogador do inicio da fila
int desenfileirar(Fila *f, Jogador *removido) {
    if (filaVazia(f)) {
        return 0;
    }

    NoFila *aux = f->inicio;

    *removido = aux->dados;
    f->inicio = aux->prox;

    free(aux);

    // Se removeu o ultimo elemento
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    return 1;
}

// Liberar toda a fila
void limparFila(Fila *f) {
    Jogador removido;

    while (desenfileirar(f, &removido));
}

// =====================================
// PROGRAMA PRINCIPAL
// =====================================

int main() {
    Pilha pilha;
    Fila fila;

    Acao a, removida, consulta;
    Jogador j, jogadorRemovido;

    inicializar(&pilha);
    inicializarFila(&fila);

    // TESTES DA PILHA
    printf("===== TESTES DA PILHA =====\n");

    a.codigo = 1;
    copiarTexto(a.descricao, "Cadastrar atendimento");
    push(&pilha, a);

    a.codigo = 2;
    copiarTexto(a.descricao, "Consultar atendimento");
    push(&pilha, a);

    a.codigo = 3;
    copiarTexto(a.descricao, "Remover atendimento");
    push(&pilha, a);

    exibir(&pilha);

    printf("\nConsultando o topo:\n");

    if (peek(&pilha, &consulta)) {
        printf("Acao: %s\n", consulta.descricao);
    }

    printf("\nInvertendo a pilha:\n");
    inverter(&pilha);
    exibir(&pilha);

    printf("\nSalvando a pilha:\n");
    salvar(&pilha);

    limpar(&pilha);

    printf("\nCarregando a pilha:\n");
    carregar(&pilha);
    exibir(&pilha);

    // TESTES DA FILA
    printf("\n===== TESTES DA FILA =====\n");

    // Teste de fila vazia
    printf("\nTeste 1 - Fila vazia:\n");

    if (filaVazia(&fila)) {
        printf("A fila esta vazia!\n");
    }

    if (!desenfileirar(&fila, &jogadorRemovido)) {
        printf("Nao existe jogador para remover!\n");
    }

    // Teste com um jogador
    printf("\nTeste 2 - Um jogador:\n");

    j.codigo = 1;
    copiarTexto(j.nome, "Carlos");

    enfileirar(&fila, j);

    exibirFila(&fila);

    // Teste com varios jogadores
    printf("\nTeste 3 - Varios jogadores:\n");

    j.codigo = 2;
    copiarTexto(j.nome, "Pedro");
    enfileirar(&fila, j);

    j.codigo = 3;
    copiarTexto(j.nome, "Joao");
    enfileirar(&fila, j);

    exibirFila(&fila);

    // Remover o primeiro jogador
    printf("\nRemovendo jogador do inicio:\n");

    if (desenfileirar(&fila, &jogadorRemovido)) {
        printf("Jogador removido: %s\n",
               jogadorRemovido.nome);
    }

    exibirFila(&fila);

    // Remover os jogadores restantes
    printf("\nEsvaziando a fila:\n");

    limparFila(&fila);

    exibirFila(&fila);

    // Liberar memoria da pilha
    limpar(&pilha);

    return 0;
}
