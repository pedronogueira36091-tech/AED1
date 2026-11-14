
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

// Consultar o topo (PEEK)
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

// Liberar todos os elementos
void limpar(Pilha *p) {
    Acao removida;

    while (pop(p, &removida));
}

// Salvar a pilha em arquivo binario
int salvar(Pilha *p) {
    FILE *arquivo = fopen("acoes.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar!\n");
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

// Carregar a pilha do arquivo binario
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
        push(p, a);

        if (p->topo == NULL || p->topo->dados.codigo != a.codigo) {
            fclose(arquivo);
            limpar(p);
            printf("Erro ao alocar memoria!\n");
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

    // Restaurar a ordem original
    inverter(p);

    printf("Pilha carregada com sucesso!\n");

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

    // Consultar o topo
    printf("\nConsultando o topo:\n");

    if (peek(&pilha, &consulta)) {
        printf("Codigo: %d\n", consulta.codigo);
        printf("Acao: %s\n", consulta.descricao);
    }

    // Remover elemento
    printf("\nRemovendo elemento:\n");

    if (pop(&pilha, &removida)) {
        printf("Acao removida: %s\n", removida.descricao);
    }

    exibir(&pilha);

    // Inserir novamente o terceiro elemento
    a.codigo = 3;

    i = 0;
    while (texto3[i] != '\0') {
        a.descricao[i] = texto3[i];
        i++;
    }
    a.descricao[i] = '\0';

    push(&pilha, a);

    // Teste de inversao
    printf("\n--- Invertendo a pilha ---\n");

    printf("\nAntes da inversao:\n");
    exibir(&pilha);

    inverter(&pilha);

    printf("\nDepois da inversao:\n");
    exibir(&pilha);

    // Salvar no arquivo
    printf("\n--- Salvando pilha ---\n");

    salvar(&pilha);

    // Limpar a pilha
    limpar(&pilha);

    printf("\nPilha depois de limpar:\n");
    exibir(&pilha);

    // Carregar do arquivo
    printf("\n--- Carregando pilha ---\n");

    carregar(&pilha);

    printf("\nPilha recuperada:\n");
    exibir(&pilha);

    // Liberar memoria
    limpar(&pilha);

    return 0;
}
