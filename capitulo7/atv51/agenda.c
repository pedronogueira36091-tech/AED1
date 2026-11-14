
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "agenda.h"

// Estrutura interna do no
struct No {
    Missao dado;
    struct No* proximo;
};

// Estrutura interna da agenda
struct Agenda {
    No* inicio;
};

// Libera uma lista de nos
static void liberarNos(No* inicio) {
    while (inicio != NULL) {
        No* proximo = inicio->proximo;
        free(inicio);
        inicio = proximo;
    }
}

// Cria a agenda
Agenda* criarAgenda(void) {
    Agenda* agenda = malloc(sizeof(Agenda));

    if (agenda != NULL) {
        agenda->inicio = NULL;
    }

    return agenda;
}

// Insere no inicio
int inserirNoInicio(Agenda* agenda, Missao m) {
    if (agenda == NULL) {
        return 0;
    }

    No* novo = malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }

    novo->dado = m;
    novo->proximo = agenda->inicio;
    agenda->inicio = novo;

    return 1;
}

// Busca por identificador
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

    No* novo = malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }

    novo->dado = m;
    novo->proximo = atual->proximo;
    atual->proximo = novo;

    return 1;
}

// Insere antes de um identificador
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

    No* novo = malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }

    novo->dado = m;
    novo->proximo = atual;

    if (anterior == NULL) {
        agenda->inicio = novo;
    } else {
        anterior->proximo = novo;
    }

    return 1;
}

// Remove o primeiro no
int removerPrimeiro(Agenda* agenda, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* atual = agenda->inicio;

    if (removida != NULL) {
        *removida = atual->dado;
    }

    agenda->inicio = atual->proximo;
    free(atual);

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

// Remove por ID
int removerPorID(Agenda* agenda, int id, Missao* removida) {
    if (agenda == NULL) {
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

// Remove depois de uma referencia
int removerDepois(Agenda* agenda, int idReferencia, Missao* removida) {
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

// Remove antes de uma referencia
int removerAntes(Agenda* agenda, int idReferencia, Missao* removida) {
    if (agenda == NULL) {
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

// Limpa a agenda
void limparAgenda(Agenda* agenda) {
    if (agenda == NULL) {
        return;
    }

    liberarNos(agenda->inicio);
    agenda->inicio = NULL;
}

// Altera uma missao
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

// Conta as missoes
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

// Insere um lote de missoes
int inserirLote(Agenda* agenda, const Missao missoes[], int quantidade) {
    if (agenda == NULL || quantidade < 0) {
        return 0;
    }

    if (quantidade == 0) {
        return 1;
    }

    if (missoes == NULL) {
        return 0;
    }

    No* primeiro = NULL;
    No* ultimo = NULL;

    for (int i = 0; i < quantidade; i++) {
        No* novo = malloc(sizeof(No));

        if (novo == NULL) {
            liberarNos(primeiro);
            return 0;
        }

        novo->dado = missoes[i];
        novo->proximo = NULL;

        if (primeiro == NULL) {
            primeiro = novo;
            ultimo = novo;
        } else {
            ultimo->proximo = novo;
            ultimo = novo;
        }
    }

    if (agenda->inicio == NULL) {
        agenda->inicio = primeiro;
    } else {
        No* atual = agenda->inicio;

        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }

        atual->proximo = primeiro;
    }

    return 1;
}

// Ordena por prioridade e, em caso de empate, pelo menor ID
void ordenarAgenda(Agenda* agenda) {
    if (agenda == NULL) {
        return;
    }

    int trocou;
    No* atual;
    No* fim = NULL;

    do {
        trocou = 0;
        atual = agenda->inicio;

        while (atual != NULL && atual->proximo != fim) {
            No* proximo = atual->proximo;

            if (atual->dado.prioridade < proximo->dado.prioridade ||
                (atual->dado.prioridade == proximo->dado.prioridade &&
                 atual->dado.id > proximo->dado.id)) {

                Missao temp = atual->dado;
                atual->dado = proximo->dado;
                proximo->dado = temp;

                trocou = 1;
            }

            atual = atual->proximo;
        }

        fim = atual;

    } while (trocou);
}

// Salva as missoes no arquivo
int salvarAgenda(const Agenda* agenda, const char* nomeArquivo) {
    if (agenda == NULL || nomeArquivo == NULL) {
        return 0;
    }

    FILE* arquivo = fopen(nomeArquivo, "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para gravacao.\n");
        return 0;
    }

    No* atual = agenda->inicio;
    int sucesso = 1;

    while (atual != NULL) {
        if (fwrite(&atual->dado, sizeof(Missao), 1, arquivo) != 1) {
            sucesso = 0;
            break;
        }

        atual = atual->proximo;
    }

    if (fclose(arquivo) != 0) {
        sucesso = 0;
    }

    return sucesso;
}

// Valida os dados lidos
static int validarMissao(const Missao* m) {
    if (m->id <= 0) {
        return 0;
    }

    if (memchr(m->descricao, '\0', sizeof(m->descricao)) == NULL) {
        return 0;
    }

    if (m->prioridade < 1 || m->prioridade > 10) {
        return 0;
    }

    return 1;
}

// Carrega as missoes preservando a ordem original
int carregarAgenda(Agenda* agenda, const char* nomeArquivo) {
    if (agenda == NULL || nomeArquivo == NULL) {
        return 0;
    }

    FILE* arquivo = fopen(nomeArquivo, "rb");

    // Se o arquivo nao existir, a agenda fica vazia
    if (arquivo == NULL) {
        if (errno == ENOENT) {
            limparAgenda(agenda);
            return 1;
        }

        printf("Erro ao abrir arquivo para leitura.\n");
        return 0;
    }

    No* primeiro = NULL;
    No* ultimo = NULL;
    Missao m;
    int sucesso = 1;

    while (1) {
        // Le exatamente o tamanho de um registro
        size_t bytes = fread(&m, 1, sizeof(Missao), arquivo);

        // Fim normal do arquivo
        if (bytes == 0 && feof(arquivo)) {
            break;
        }

        // Registro incompleto ou erro de leitura
        if (bytes != sizeof(Missao)) {
            sucesso = 0;
            break;
        }

        // Valida antes de inserir
        if (!validarMissao(&m)) {
            sucesso = 0;
            break;
        }

        // Evita IDs repetidos no arquivo
        No* teste = primeiro;
        int duplicado = 0;

        while (teste != NULL) {
            if (teste->dado.id == m.id) {
                duplicado = 1;
                break;
            }

            teste = teste->proximo;
        }

        if (duplicado) {
            sucesso = 0;
            break;
        }

        No* novo = malloc(sizeof(No));

        if (novo == NULL) {
            sucesso = 0;
            break;
        }

        novo->dado = m;
        novo->proximo = NULL;

        // Insere no final para preservar a ordem gravada
        if (primeiro == NULL) {
            primeiro = novo;
            ultimo = novo;
        } else {
            ultimo->proximo = novo;
            ultimo = novo;
        }
    }

    if (ferror(arquivo)) {
        sucesso = 0;
    }

    if (fclose(arquivo) != 0) {
        sucesso = 0;
    }

    // Em caso de erro, descarta a lista temporaria
    if (!sucesso) {
        liberarNos(primeiro);
        printf("Erro: arquivo invalido ou falha na leitura.\n");
        return 0;
    }

    // Substitui a agenda somente depois de validar tudo
    limparAgenda(agenda);
    agenda->inicio = primeiro;

    return 1;
}

// Exibe as missoes
void exibirAgenda(const Agenda* agenda) {
    if (agenda == NULL || agenda->inicio == NULL) {
        printf("\nA agenda esta vazia.\n");
        return;
    }

    No* atual = agenda->inicio;

    printf("\n--- Agenda de Missoes ---\n");

    while (atual != NULL) {
        printf("ID: %d | Descricao: %s | Prioridade: %d\n",
               atual->dado.id,
               atual->dado.descricao,
               atual->dado.prioridade);

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
