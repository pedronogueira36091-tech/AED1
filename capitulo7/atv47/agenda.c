
// Remove a missao imediatamente depois da referencia
int removerDepois(Agenda* agenda, int idReferencia, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    // Busca a missao de referencia
    No* referencia = buscarMissao(agenda, idReferencia);

    // Verifica se a referencia existe e possui um sucessor
    if (referencia == NULL || referencia->proximo == NULL) {
        return 0;
    }

    // No que sera removido
    No* atual = referencia->proximo;

    // Guarda os dados antes de liberar
    if (removida != NULL) {
        *removida = atual->dado;
    }

    // Liga a referencia ao sucessor do no removido
    referencia->proximo = atual->proximo;

    // Libera o no removido
    free(atual);

    return 1;
}

// Remove a missao imediatamente antes da referencia
int removerAntes(Agenda* agenda, int idReferencia, Missao* removida) {
    if (agenda == NULL || agenda->inicio == NULL) {
        return 0;
    }

    No* anteriorAnterior = NULL;
    No* anterior = NULL;
    No* atual = agenda->inicio;

    // Procura a referencia mantendo os nos anteriores
    while (atual != NULL && atual->dado.id != idReferencia) {
        anteriorAnterior = anterior;
        anterior = atual;
        atual = atual->proximo;
    }

    // Referencia nao encontrada ou nao existe no anterior
    if (atual == NULL || anterior == NULL) {
        return 0;
    }

    // Guarda os dados antes de liberar
    if (removida != NULL) {
        *removida = anterior->dado;
    }

    // Se o removido for o primeiro, atualiza o inicio
    if (anteriorAnterior == NULL) {
        agenda->inicio = atual;
    } else {
        // Liga o no anterior ao anterior do removido
        anteriorAnterior->proximo = atual;
    }

    // Libera exatamente o no removido
    free(anterior);

    return 1;
}
