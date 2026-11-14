
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

// Representa um nó
struct No {
    Missao dado;
    struct No* proximo;
};

// Representa a Agenda
struct Agenda {
    No* inicio;
};

// Inicializa a lista vazia
Agenda* criarAgenda(void) {
    Agenda* agenda = (Agenda*)malloc(sizeof(Agenda));

    if (agenda != NULL) {
        agenda->inicio = NULL;
    }

    return agenda;
}

// Insere uma missão no início
int inserirNoInicio(Agenda* agenda, Missao m) {
    if (agenda == NULL) {
        return 0;
    }

    No* novoNo = (No*)malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 0;
    }

    novoNo->dado = m;
    novoNo->proximo = agenda->inicio;
    agenda->inicio = novoNo;

    return 1;
}

// Busca uma missão pelo ID
No* buscarMissao(const Agenda* agenda, int id) {
    if (agenda == NULL) {
        return NULL;
    }

    No* atual = agenda->inicio;

    while (atual != NULL) {
        if (atual->dado.id == id) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

// Insere uma missão depois da referência
int inserirDepois(Agenda* agenda, No* referencia, Missao m) {
    if (agenda == NULL || referencia == NULL) {
        return 0;
    }

    // Verifica se a referência pertence à agenda
    No* atual = agenda->inicio;

    while (atual != NULL && atual != referencia) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 0;
    }

    // Aloca o novo nó
    No* novoNo = (No*)malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 0;
    }

    // Liga o novo nó ao antigo sucessor
    novoNo->dado = m;
    novoNo->proximo = referencia->proximo;

    // Atualiza a referência
    referencia->proximo = novoNo;

    return 1;
}

// Exibe todas as missões
void exibirAgenda(const Agenda* agenda) {
    if (agenda == NULL || agenda->inicio == NULL) {
        printf("\nA agenda esta vazia.\n");
        return;
    }

    printf("\n--- Agenda de Missoes ---\n");

    No* atual = agenda->inicio;

    while (atual != NULL) {
        printf("[ID: %d] Descricao: %s\n",
               atual->dado.id,
               atual->dado.descricao);

        atual = atual->proximo;
    }

    printf("-------------------------\n");
}

// Libera a memória
void destruirAgenda(Agenda* agenda) {
    if (agenda == NULL) {
        return;
    }

    No* atual = agenda->inicio;

    while (atual != NULL) {
        No* aux = atual->proximo;
        free(atual);
        atual = aux;
    }

    free(agenda);
}
