#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

// Representa um nó com dado e ponteiro para o próximo
typedef struct No {
    Missao dado;
    struct No* proximo;
} No;

// Representa a Agenda propriamente dita (encapsula o ponteiro do início)
struct Agenda {
    No* inicio;
};

// Inicializa a lista vazia
Agenda* criarAgenda(void) {
    Agenda* agenda = (Agenda*)malloc(sizeof(Agenda));
    if (agenda != NULL) {
        agenda->inicio = NULL; // Lista começa vazia
    }
    return agenda;
}

// Insere uma nova missão no início da lista
int inserirNoInicio(Agenda* agenda, Missao m) {
    if (agenda == NULL) {
        return 0; // Falha se a agenda não for válida
    }

    // 1. Alocar o novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    
    // Validar a alocação do novo nó
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o novo no.\n");
        return 0; // Falha na alocação
    }

    // 2. Copiar os dados da missão para o nó
    novoNo->dado = m;

    // 3. Conectar antes do antigo primeiro nó
    novoNo->proximo = agenda->inicio;

    // 4. Atualizar corretamente o início da lista
    agenda->inicio = novoNo;

    return 1; // Sucesso na inserção
}

// Exibe todas as missões da agenda
void exibirAgenda(const Agenda* agenda) {
    if (agenda == NULL || agenda->inicio == NULL) {
        printf("\nA agenda esta vazia.\n");
        return;
    }

    printf("\n--- Agenda de Missoes ---\n");
    No* atual = agenda->inicio;
    while (atual != NULL) {
        printf("[ID: %d] Descricao: %s\n", atual->dado.id, atual->dado.descricao);
        atual = atual->proximo;
    }
    printf("-------------------------\n");
}

// Libera a memória alocada para a agenda e seus nós
void destruirAgenda(Agenda* agenda) {
    if (agenda == NULL) return;

    No* atual = agenda->inicio;
    while (atual != NULL) {
        No* aux = atual->proximo;
        free(atual);
        atual = aux;
    }
    free(agenda);
}