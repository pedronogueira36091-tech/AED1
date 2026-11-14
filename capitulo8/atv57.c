
#include <stdio.h>
#include <stdlib.h>

// =====================================
// ESTRUTURAS
// =====================================

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

// =====================================
// FUNCOES AUXILIARES
// =====================================

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

// Inicializar pilha
void inicializar(Pilha *p) {
    p->topo = NULL;
}

// Verificar se esta vazia
int esta_vazia(Pilha *p) {
    return p->topo == NULL;
}

// Inserir no topo (PUSH)
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

// Consultar topo (PEEK)
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
        printf("Historico vazio!\n");
        return;
    }

    printf("\n--- Historico de atendimentos ---\n");

    while (aux != NULL) {
        printf("Codigo: %d | Acao: %s\n",
               aux->dados.codigo,
               aux->dados.descricao);

        aux = aux->prox;
    }
}

// Remover do topo (POP)
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

// =====================================
// PERSISTENCIA DA PILHA
// =====================================

// Salvar pilha
int salvarPilha(Pilha *p) {
    FILE *arquivo = fopen("acoes.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao salvar historico!\n");
        return 0;
    }

    No *aux = p->topo;

    while (aux != NULL) {
        if (fwrite(&aux->dados, sizeof(Acao), 1,
                   arquivo) != 1) {
            fclose(arquivo);
            return 0;
        }

        aux = aux->prox;
    }

    if (fclose(arquivo) != 0) {
        return 0;
    }

    return 1;
}

// Carregar pilha
int carregarPilha(Pilha *p) {
    FILE *arquivo;
    Acao a;
    size_t lidos;

    arquivo = fopen("acoes.dat", "rb");

    if (arquivo == NULL) {
        printf("Historico ainda nao possui arquivo.\n");
        return 0;
    }

    limpar(p);

    while ((lidos = fread(&a, 1, sizeof(Acao),
                          arquivo)) == sizeof(Acao)) {

        if (!push(p, a)) {
            fclose(arquivo);
            limpar(p);
            return 0;
        }
    }

    if (lidos != 0 || ferror(arquivo)) {
        fclose(arquivo);
        limpar(p);
        printf("Erro na leitura do historico!\n");
        return 0;
    }

    if (fclose(arquivo) != 0) {
        limpar(p);
        return 0;
    }

    // Restaurar a ordem original
    inverter(p);

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

// Consultar inicio (FRONT)
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

// Remover do inicio (DEQUEUE)
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
// PERSISTENCIA DA FILA
// =====================================

// Salvar fila
int salvarFila(Fila *f) {
    FILE *arquivo = fopen("fila.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao salvar fila!\n");
        return 0;
    }

    NoFila *aux = f->inicio;

    // Salvar do inicio ate o fim
    while (aux != NULL) {
        if (fwrite(&aux->dados, sizeof(Jogador), 1,
                   arquivo) != 1) {
            fclose(arquivo);
            return 0;
        }

        aux = aux->prox;
    }

    if (fclose(arquivo) != 0) {
        return 0;
    }

    return 1;
}

// Carregar fila
int carregarFila(Fila *f) {
    FILE *arquivo;
    Jogador j;
    size_t lidos;

    arquivo = fopen("fila.dat", "rb");

    if (arquivo == NULL) {
        printf("Arquivo da fila nao encontrado.\n");
        return 0;
    }

    // Evitar duplicacao
    limparFila(f);

    // Ler e inserir no final
    while ((lidos = fread(&j, 1, sizeof(Jogador),
                          arquivo)) == sizeof(Jogador)) {

        if (!enfileirar(f, j)) {
            fclose(arquivo);
            limparFila(f);
            return 0;
        }
    }

    if (lidos != 0 || ferror(arquivo)) {
        fclose(arquivo);
        limparFila(f);
        printf("Erro na leitura da fila!\n");
        return 0;
    }

    if (fclose(arquivo) != 0) {
        limparFila(f);
        return 0;
    }

    return 1;
}

// =====================================
// SALVAR E CARREGAR TUDO
// =====================================

void salvarTudo(Pilha *p, Fila *f) {
    int resultadoPilha;
    int resultadoFila;

    resultadoPilha = salvarPilha(p);
    resultadoFila = salvarFila(f);

    if (resultadoPilha && resultadoFila) {
        printf("\nDados salvos com sucesso!\n");
    } else {
        printf("\nErro ao salvar todos os dados!\n");
    }
}

void carregarTudo(Pilha *p, Fila *f) {
    if (carregarPilha(p)) {
        printf("Historico carregado!\n");
    }

    if (carregarFila(f)) {
        printf("Fila carregada!\n");
    }
}

// =====================================
// CADASTRAR JOGADOR
// =====================================

void cadastrar(Fila *f) {
    Jogador j;

    printf("\nCodigo do jogador: ");

    if (scanf("%d", &j.codigo) != 1) {
        printf("Codigo invalido!\n");

        while (getchar() != '\n');
        return;
    }

    printf("Nome do jogador: ");

    if (scanf(" %99[^\n]", j.nome) != 1) {
        printf("Nome invalido!\n");
        return;
    }

    if (enfileirar(f, j)) {
        printf("\nJogador cadastrado com sucesso!\n");
    }
}

// =====================================
// CONSULTAR PROXIMO JOGADOR
// =====================================

void consultar(Fila *f) {
    Jogador j;

    if (front(f, &j)) {
        printf("\nProximo jogador:\n");
        printf("Codigo: %d\n", j.codigo);
        printf("Nome: %s\n", j.nome);
    } else {
        printf("\nNao existe jogador na fila!\n");
    }
}

// =====================================
// REALIZAR ATENDIMENTO
// =====================================

void atender(Fila *f, Pilha *p) {
    Jogador j;
    Jogador removido;
    Acao a;
    char confirmacao;

    if (!front(f, &j)) {
        printf("\nFila vazia!\n");
        return;
    }

    printf("\nProximo jogador: %s\n", j.nome);

    printf("Confirmar atendimento? (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {

        // Preparar registro
        a.codigo = j.codigo;
        copiarTexto(a.descricao, "Atendimento concluido");

        // Registrar antes de remover da fila
        if (!push(p, a)) {
            printf("Atendimento nao realizado!\n");
            return;
        }

        if (desenfileirar(f, &removido)) {
            printf("\nAtendimento realizado!\n");
            printf("Jogador: %s\n", removido.nome);
        }

    } else {
        printf("\nAtendimento cancelado!\n");
        printf("Jogador continua na fila.\n");
    }
}

// =====================================
// AUDITAR HISTORICO
// =====================================

void auditar(Pilha *p) {
    Acao a;

    printf("\n===== AUDITORIA =====\n");

    if (peek(p, &a)) {
        printf("Ultima acao registrada:\n");
        printf("Codigo: %d\n", a.codigo);
        printf("Descricao: %s\n", a.descricao);
    } else {
        printf("Nenhuma acao registrada.\n");
    }

    exibir(p);
}

// =====================================
// MENU PRINCIPAL
// =====================================

int main() {
    Pilha pilha;
    Fila fila;

    int opcao;

    inicializar(&pilha);
    inicializarFila(&fila);

    printf("===== GERENCIADOR DE ATENDIMENTOS =====\n");

    // Recuperar dados anteriores
    carregarTudo(&pilha, &fila);

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");

        printf("1 - Cadastrar jogador\n");
        printf("2 - Consultar proximo jogador\n");
        printf("3 - Realizar atendimento\n");
        printf("4 - Auditar historico\n");
        printf("5 - Salvar dados\n");
        printf("6 - Carregar dados\n");
        printf("7 - Exibir fila\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida!\n");

            while (getchar() != '\n');

            opcao = -1;
            continue;
        }

        switch (opcao) {

            case 1:
                cadastrar(&fila);
                break;

            case 2:
                consultar(&fila);
                break;

            case 3:
                atender(&fila, &pilha);
                break;

            case 4:
                auditar(&pilha);
                break;

            case 5:
                salvarTudo(&pilha, &fila);
                break;

            case 6:
                carregarTudo(&pilha, &fila);
                break;

            case 7:
                exibirFila(&fila);
                break;

            case 0:
                printf("\nSalvando dados antes de sair...\n");

                salvarTudo(&pilha, &fila);

                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    // Liberar toda a memoria
    limpar(&pilha);
    limparFila(&fila);

    printf("Memoria liberada com sucesso!\n");

    return 0;
}
