
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

// Representa um no da lista
struct No {
    Missao dado;
    struct No* proximo;
};

// Representa a Agenda
struct Agenda {
    No* inicio;
};

// Cria uma agenda vazia
Agenda* criarAgenda(void) {
    Agenda* agenda = (Agenda*)malloc(sizeof(Agenda));

    if (agenda != NULL) {
        agenda->inicio = NULL;
    }

    return agenda;
}

// Insere uma missao no inicio
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

// Busca uma missao pelo ID
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

// Insere depois de uma referencia
int inserirDepois(Agenda* agenda, No* referencia, Missao m) {
    if (agenda == NULL || referencia == NULL) {
        return 0;
    }

    // Verifica se a referencia pertence a agenda
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

// Insere antes de um ID
int inserirAntes(Agenda* agenda, int idReferencia, Missao m) {
    if (agenda == NULL) {
        return 0;
    }

    No* anterior = NULL;
    No* atual = agenda->inicio;

    while (atual != NULL && atual->dado.id != idReferencia) {
        anterior = atual;
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
    novoNo->proximo = atual;

    if (anterior == NULL) {
        agenda->inicio = novoNo;
    } else {
        anterior->proximo = novoNo;
    }

    return 1;
}

// Remove o primeiro no
int removerPrimeiro(Agenda* agenda, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* primeiro = agenda->inicio;

    if (removida != NULL) {
        *removida = primeiro->dado;
    }

    agenda->inicio = primeiro->proximo;

    free(primeiro);

    return 1;
}

// Remove o ultimo no
int removerUltimo(Agenda* agenda, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* atual = agenda->inicio;
    No* anterior = NULL;

    while (atual->proximo != NULL) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (removida != NULL) {
        *removida = atual->dado;
    }

    if (anterior == NULL) {
        agenda->inicio = NULL;
    } else {
        anterior->proximo = NULL;
    }

    free(atual);

    return 1;
}

// Remove uma missao pelo ID
int removerPorID(Agenda* agenda, int id, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* atual = agenda->inicio;
    No* anterior = NULL;

    while (atual != NULL && atual->dado.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 0;
    }

    if (removida != NULL) {
        *removida = atual->dado;
    }

    if (anterior == NULL) {
        agenda->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);

    return 1;
}

// Remove a missao depois da referencia
int removerDepois(Agenda* agenda, int idReferencia, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* referencia = buscarMissao(agenda, idReferencia);

    if (referencia == NULL || referencia->proximo == NULL) {
        return 0;
    }

    No* atual = referencia->proximo;

    if (removida != NULL) {
        *removida = atual->dado;
    }

    referencia->proximo = atual->proximo;

    free(atual);

    return 1;
}

// Remove a missao antes da referencia
int removerAntes(Agenda* agenda, int idReferencia, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* anteriorAnterior = NULL;
    No* anterior = NULL;
    No* atual = agenda->inicio;

    while (atual != NULL && atual->dado.id != idReferencia) {
        anteriorAnterior = anterior;
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL || anterior == NULL) {
        return 0;
    }

    if (removida != NULL) {
        *removida = anterior->dado;
    }

    if (anteriorAnterior == NULL) {
        agenda->inicio = atual;
    } else {
        anteriorAnterior->proximo = atual;
    }

    free(anterior);

    return 1;
}

// NOVA FUNCAO: Limpa toda a agenda
void limparAgenda(Agenda* agenda) {
    if (agenda == NULL) {
        return;
    }

    No* atual = agenda->inicio;

    while (atual != NULL) {
        // Salva o proximo antes de liberar o atual
        No* proximo = atual->proximo;

        free(atual);

        atual = proximo;
    }

    // A agenda fica vazia
    agenda->inicio = NULL;
}

// NOVA FUNCAO: Altera a descricao de uma missao
int alterarMissao(Agenda* agenda, int id, const char* novaDescricao) {
    // Valida a agenda e a nova descricao
    if (agenda == NULL || novaDescricao == NULL ||
        novaDescricao[0] == '\0') {
        return 0;
    }

    // Procura a missao pelo ID
    No* atual = buscarMissao(agenda, id);

    if (atual == NULL) {
        return 0;
    }

    // Altera somente a descricao
    // O identificador permanece inalterado
    strncpy(atual->dado.descricao, novaDescricao,
            sizeof(atual->dado.descricao) - 1);

    atual->dado.descricao[
        sizeof(atual->dado.descricao) - 1
    ] = '\0';

    return 1;
}

// Exibe todas as missoes
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

// Destroi a agenda e libera toda a memoria
void destruirAgenda(Agenda* agenda) {
    if (agenda == NULL) {
        return;
    }

    // Limpa todos os nos antes de liberar a agenda
    limparAgenda(agenda);

    free(agenda);
}
