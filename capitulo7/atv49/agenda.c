
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

// Limpa toda a agenda
void limparAgenda(Agenda* agenda) {
    if (agenda == NULL) {
        return;
    }

    No* atual = agenda->inicio;

    while (atual != NULL) {
        No* proximo = atual->proximo;

        free(atual);

        atual = proximo;
    }

    agenda->inicio = NULL;
}

// Altera a descricao de uma missao
int alterarMissao(Agenda* agenda, int id, const char* novaDescricao) {
    if (agenda == NULL || novaDescricao == NULL ||
        novaDescricao[0] == '\0') {
        return 0;
    }

    No* atual = buscarMissao(agenda, id);

    if (atual == NULL) {
        return 0;
    }

    strncpy(atual->dado.descricao, novaDescricao,
            sizeof(atual->dado.descricao) - 1);

    atual->dado.descricao[
        sizeof(atual->dado.descricao) - 1
    ] = '\0';

    return 1;
}

// NOVA FUNCAO: Conta as missoes da agenda
int tamanhoAgenda(const Agenda* agenda) {
    if (agenda == NULL) {
        return 0;
    }

    int quantidade = 0;
    No* atual = agenda->inicio;

    while (atual != NULL) {
        quantidade++;
        atual = atual->proximo;
    }

    return quantidade;
}

// NOVA FUNCAO: Insere varias missoes em lote
int inserirLote(Agenda* agenda, const Missao missoes[], int quantidade) {
    // Valida a agenda e a quantidade
    if (agenda == NULL || quantidade < 0) {
        return 0;
    }

    // Lote vazio: nenhuma alteracao
    if (quantidade == 0) {
        return 1;
    }

    if (missoes == NULL) {
        return 0;
    }

    No* primeiroNovo = NULL;
    No* ultimoNovo = NULL;

    // Cria todos os nos antes de alterar a agenda
    for (int i = 0; i < quantidade; i++) {
        No* novoNo = (No*)malloc(sizeof(No));

        // Se falhar, libera o lote temporario
        if (novoNo == NULL) {
            No* atual = primeiroNovo;

            while (atual != NULL) {
                No* proximo = atual->proximo;
                free(atual);
                atual = proximo;
            }

            return 0;
        }

        novoNo->dado = missoes[i];
        novoNo->proximo = NULL;

        // Monta a lista temporaria na ordem de entrada
        if (primeiroNovo == NULL) {
            primeiroNovo = novoNo;
            ultimoNovo = novoNo;
        } else {
            ultimoNovo->proximo = novoNo;
            ultimoNovo = novoNo;
        }
    }

    // Se a agenda estiver vazia, o lote sera o inicio
    if (agenda->inicio == NULL) {
        agenda->inicio = primeiroNovo;
    } else {
        // Procura o ultimo no da agenda
        No* atual = agenda->inicio;

        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }

        // Conecta o lote ao final da agenda
        atual->proximo = primeiroNovo;
    }

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

// Destroi a agenda
void destruirAgenda(Agenda* agenda) {
    if (agenda == NULL) {
        return;
    }

    limparAgenda(agenda);

    free(agenda);
}
