#include <stdio.h>
#include "agenda.h"

int main() {
    // Inicializa a agenda vazia através da interface pública
    Agenda* minhaAgenda = criarAgenda();

    if (minhaAgenda == NULL) {
        printf("Erro ao criar a agenda.\n");
        return 1;
    }

    // Criando algumas missões de teste
    Missao m1 = {1, "Explorar a caverna principal"};
    Missao m2 = {2, "Coletar 5 ervas medicinais"};
    Missao m3 = {3, "Entregar a carta ao ferreiro"};

    // Inserindo no início da lista
    printf("Inserindo missao 1...\n");
    inserirNoInicio(minhaAgenda, m1);

    printf("Inserindo missao 2 no inicio...\n");
    inserirNoInicio(minhaAgenda, m2);

    printf("Inserindo missao 3 no inicio...\n");
    inserirNoInicio(minhaAgenda, m3);

    // Como as inserções ocorrem no início, a ordem de exibição será 3 -> 2 -> 1
    exibirAgenda(minhaAgenda);

    // Libera a memória da agenda ao finalizar
    destruirAgenda(minhaAgenda);

    return 0;
}