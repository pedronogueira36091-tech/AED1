
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

// Insere depois de uma referência
int inserirDepois(Agenda* agenda, No* referencia, Missao m) {
    if (agenda == NULL || referencia == NULL) {
        return 0;
    }

    No* atual = agenda->inicio;

    while (atual != NULL && atual != referencia) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 0;
    }

    No* novoNo = (No*)malloc(sizeof(No));

    if (novoNo == NULL) {
        return 0;
    }

    novoNo->dado = m;
    novoNo->proximo = referencia->proximo;
    referencia->proximo = novoNo;

    return 1;
}

// NOVA FUNÇÃO: Insere antes de um ID
int inserirAntes(Agenda* agenda, int idReferencia, Missao m) {
    if (agenda == NULL) {
        return 0;
    }

    No* anterior = NULL;
    No* atual = agenda->inicio;

    // Busca mantendo o anterior e o atual
    while (atual != NULL && atual->dado.id != idReferencia) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Referência não encontrada
    if (atual == NULL) {
        return 0;
    }

    // Aloca o novo nó somente após encontrar a referência
    No* novoNo = (No*)malloc(sizeof(No));

    if (novoNo == NULL) {
        return 0;
    }

    novoNo->dado = m;
    novoNo->proximo = atual;

    // Se for o primeiro nó, atualiza o início
    if (anterior == NULL) {
        agenda->inicio = novoNo;
    } else {
        anterior->proximo = novoNo;
    }

    return 1;
}

// NOVA FUNÇÃO: Remove o primeiro nó
int removerPrimeiro(Agenda* agenda, Missao* removida) {
    // Verifica se a agenda está vazia
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* primeiro = agenda->inicio;

    // Guarda os dados antes de liberar a memória
    if (removida != NULL) {
        *removida = primeiro->dado;
    }

    // Atualiza o início da lista
    agenda->inicio = primeiro->proximo;

    // Libera o primeiro nó
    free(primeiro);

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
