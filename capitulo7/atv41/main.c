#include <stdio.h>
#include "agenda.h"

int main() {
    printf("=== Teste do Modulo Agenda de Missoes ===\n\n");

    // Criação de missões utilizando a interface do módulo
    Missao m1 = criarMissao(1, "Explorar nova area no mapa");
    Missao m2 = criarMissao(2, "Derrotar o chefe do nivel 3");

    // Exibição das missões criadas
    printf("Lista de Missoes Criadas:\n");
    exibirMissao(m1);
    exibirMissao(m2);

    return 0;
}