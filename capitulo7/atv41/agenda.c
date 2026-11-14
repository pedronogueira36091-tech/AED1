#include <stdio.h>
#include <string.h>
#include "agenda.h"

// Função para criar e inicializar uma missão
Missao criarMissao(int id, const char* descricao) {
    Missao m;
    m.id = id;
    
    // Copia a descrição de forma segura para a struct
    strncpy(m.descricao, descricao, sizeof(m.descricao) - 1);
    m.descricao[sizeof(m.descricao) - 1] = '\0'; // Garante o terminação com caractere nulo
    
    return m;
}

// Função para exibir os dados de uma missão
void exibirMissao(Missao m) {
    printf("[ID: %d] Descricao: %s\n", m.id, m.descricao);
}