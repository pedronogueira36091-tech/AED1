
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

// Inicializar a pilha
void inicializar(Pilha *p) {
    p->topo = NULL;
}

// Verificar se a pilha esta vazia
int esta_vazia(Pilha *p) {
    return p->topo == NULL;
}

// Inserir elemento no topo (PUSH)
void push(Pilha *p, Acao a) {
    No *novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    novo->dados = a;
    novo->prox = p->topo;
    p->topo = novo;
}

// Consultar o topo sem remover (PEEK)
int peek(Pilha *p, Acao *consulta) {
    if (esta_vazia(p)) {
        return 0;
    }

    *consulta = p->topo->dados;

    return 1;
}

// Exibir elementos da pilha
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

// Remover elemento do topo (POP)
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

// Programa principal
int main() {
    Pilha pilha;
    Acao a, removida, consulta;
    int i;

    inicializar(&pilha);

    // Teste 1: pilha vazia
    printf("Teste 1 - Pilha vazia:\n");

    if (esta_vazia(&pilha)) {
        printf("A pilha esta vazia!\n");
    }

    if (!peek(&pilha, &consulta)) {
        printf("Nao existe elemento no topo!\n");
    }

    if (!pop(&pilha, &removida)) {
        printf("Nao existe elemento para remover!\n");
    }

    // Teste 2: inserir um elemento
    printf("\nTeste 2 - Um elemento:\n");

    a.codigo = 1;

    char texto1[] = "Cadastrar atendimento";

    i = 0;
    while (texto1[i] != '\0') {
        a.descricao[i] = texto1[i];
        i++;
    }
    a.descricao[i] = '\0';

    push(&pilha, a);

    exibir(&pilha);

    // Teste 3: inserir varios elementos
    printf("\nTeste 3 - Varios elementos:\n");

    a.codigo = 2;

    char texto2[] = "Consultar atendimento";

    i = 0;
    while (texto2[i] != '\0') {
        a.descricao[i] = texto2[i];
        i++;
    }
    a.descricao[i] = '\0';

    push(&pilha, a);

    a.codigo = 3;

    char texto3[] = "Remover atendimento";

    i = 0;
    while (texto3[i] != '\0') {
        a.descricao[i] = texto3[i];
        i++;
    }
    a.descricao[i] = '\0';

    push(&pilha, a);

    exibir(&pilha);

    // Verificar se a pilha esta vazia
    if (!esta_vazia(&pilha)) {
        printf("\nA pilha possui elementos!\n");
    }

    // Consultar o topo antes de remover
    printf("\nConsultando o topo da pilha:\n");

    if (peek(&pilha, &consulta)) {
        printf("Codigo: %d\n", consulta.codigo);
        printf("Acao: %s\n", consulta.descricao);
    } else {
        printf("Nao foi possivel consultar o topo!\n");
    }

    // Exibir novamente para provar que nada foi removido
    printf("\nPilha depois da consulta:\n");
    exibir(&pilha);

    // Remover elemento do topo
    printf("\nRemovendo elemento do topo:\n");

    if (pop(&pilha, &removida)) {
        printf("Acao removida: %s\n", removida.descricao);
    }

    exibir(&pilha);

    // Liberar memoria restante
    while (pop(&pilha, &removida));

    return 0;
}
