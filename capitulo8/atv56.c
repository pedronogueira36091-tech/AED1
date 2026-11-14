
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

// Copiar texto sem string.h
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

void inicializar(Pilha *p) {
    p->topo = NULL;
}

int esta_vazia(Pilha *p) {
    return p->topo == NULL;
}

// PUSH
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

// PEEK
int peek(Pilha *p, Acao *consulta) {
    if (esta_vazia(p)) {
        return 0;
    }

    *consulta = p->topo->dados;

    return 1;
}

// Exibir pilha
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

// POP
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

// Inverter pilha
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

// Limpar pilha
void limpar(Pilha *p) {
    Acao removida;

    while (pop(p, &removida));
}

// Salvar pilha
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

// Carregar pilha
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

    while ((lidos = fread(&a, 1, sizeof(Acao), arquivo))
           == sizeof(Acao)) {

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

// Inicializar fila
void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Verificar fila vazia
int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

// Inserir no final (ENFILEIRAR)
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

// Consultar primeiro jogador (FRONT)
int front(Fila *f, Jogador *consulta) {
    if (filaVazia(f)) {
        return 0;
    }

    *consulta = f->inicio->dados;

    return 1;
}

// Exibir fila
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

// Remover primeiro jogador (DEQUEUE)
int desenfileirar(Fila *f, Jogador *removido) {
    if (filaVazia(f)) {
        return 0;
    }

    NoFila *aux = f->inicio;

    *removido = aux->dados;
    f->inicio = aux->prox;

    free(aux);

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    return 1;
}

// Limpar fila
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
    Jogador j, proximo, jogadorRemovido;

    char confirmacao;

    inicializar(&pilha);
    inicializarFila(&fila);

    printf("===== ATIVIDADE 56 =====\n");

    // Inserir jogadores na fila
    printf("\nInserindo jogadores na fila:\n");

    j.codigo = 1;
    copiarTexto(j.nome, "Carlos");
    enfileirar(&fila, j);

    j.codigo = 2;
    copiarTexto(j.nome, "Pedro");
    enfileirar(&fila, j);

    j.codigo = 3;
    copiarTexto(j.nome, "Joao");
    enfileirar(&fila, j);

    exibirFila(&fila);

    // Consultar primeiro jogador
    printf("\n===== CONSULTA AO INICIO =====\n");

    if (front(&fila, &proximo)) {
        printf("Proximo jogador: %s\n", proximo.nome);
        printf("Codigo: %d\n", proximo.codigo);
    } else {
        printf("Nao existe jogador na fila!\n");
    }

    // Mostrar que a fila continua igual
    printf("\nFila antes da confirmacao:\n");
    exibirFila(&fila);

    // Confirmar atendimento
    printf("\nDeseja confirmar o atendimento? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {

        // Remover somente depois da confirmacao
        if (desenfileirar(&fila, &jogadorRemovido)) {

            printf("\nAtendimento confirmado!\n");
            printf("Jogador atendido: %s\n",
                   jogadorRemovido.nome);

            // Registrar atendimento na pilha
            a.codigo = jogadorRemovido.codigo;

            copiarTexto(a.descricao,
                        "Atendimento concluido");

            if (push(&pilha, a)) {
                printf("Atendimento registrado no historico!\n");
            }

        } else {
            printf("Nao foi possivel realizar o atendimento!\n");
        }

    } else {
        printf("\nAtendimento nao confirmado!\n");
        printf("O jogador continua na fila.\n");
    }

    // Mostrar nova fila
    printf("\n===== FILA ATUALIZADA =====\n");
    exibirFila(&fila);

    // Mostrar novo topo da pilha
    printf("\n===== TOPO DA PILHA =====\n");

    if (peek(&pilha, &consulta)) {
        printf("Codigo: %d\n", consulta.codigo);
        printf("Acao: %s\n", consulta.descricao);
    } else {
        printf("Nenhum atendimento registrado!\n");
    }

    // Exibir historico completo
    printf("\n===== HISTORICO COMPLETO =====\n");
    exibir(&pilha);

    // Liberar memoria
    limparFila(&fila);
    limpar(&pilha);

    return 0;
}
