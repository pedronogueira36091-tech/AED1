
// Remove a ultima missao da agenda
int removerUltimo(Agenda* agenda, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* atual = agenda->inicio;
    No* anterior = NULL;

    // Percorre ate encontrar o ultimo no
    while (atual->proximo != NULL) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Guarda os dados antes de liberar
    if (removida != NULL) {
        *removida = atual->dado;
    }

    // Se so existe um no, a lista fica vazia
    if (anterior == NULL) {
        agenda->inicio = NULL;
    } else {
        anterior->proximo = NULL;
    }

    // Libera exatamente o ultimo no
    free(atual);

    return 1;
}

// Remove a primeira missao com o ID informado
int removerPorID(Agenda* agenda, int id, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* atual = agenda->inicio;
    No* anterior = NULL;

    // Procura a missao pelo identificador
    while (atual != NULL && atual->dado.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    // ID nao encontrado
    if (atual == NULL) {
        return 0;
    }

    // Guarda os dados antes de liberar
    if (removida != NULL) {
        *removida = atual->dado;
    }

    // Se for o primeiro no, atualiza o inicio
    if (anterior == NULL) {
        agenda->inicio = atual->proximo;
    } else {
        // Liga o anterior ao proximo do atual
        anterior->proximo = atual->proximo;
    }

    // Libera o no removido
    free(atual);

    return 1;
}
