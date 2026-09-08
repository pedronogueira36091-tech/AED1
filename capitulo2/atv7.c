#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define TAM_APELIDO 15
#define TAM_SENHA 20

#define MAX_COMP_APELIDO 10

void ler_string(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);

    size_t len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int main() {
    char nome[TAM_NOME];
    char apelido[TAM_APELIDO];
    char senha[TAM_SENHA];
    char confirmacao_senha[TAM_SENHA];

    int apelido_valido = 0;
    int senha_valida = 0;

    printf("CADASTRO DE JOGADOR\n\n");

    printf("Digite o nome completo: ");
    ler_string(nome, TAM_NOME);

    do {
        printf("Digite o apelido (máximo de %d caracteres): ", MAX_COMP_APELIDO);
        ler_string(apelido, TAM_APELIDO);

        if (strlen(apelido) > MAX_COMP_APELIDO) {
            printf("[ERRO] Apelido muito longo! O apelido deve ter no máximo %d caracteres.\n\n", MAX_COMP_APELIDO);
        } else if (strlen(apelido) == 0) {
            printf("[ERRO] O apelido não pode ser vazio.\n\n");
        } else {
            apelido_valido = 1;
        }
    } while (!apelido_valido);

    do {
        printf("Digite a senha: ");
        ler_string(senha, TAM_SENHA);

        printf("Confirme a senha: ");
        ler_string(confirmacao_senha, TAM_SENHA);

        if (strcmp(senha, confirmacao_senha) != 0) {
            printf("[ERRO] As senhas não coincidem. Digite novamente.\n\n");
        } else if (strlen(senha) == 0) {
            printf("[ERRO] A senha não pode ser vazia.\n\n");
        } else {
            senha_valida = 1;
        }
    } while (!senha_valida);

    printf("\nCADASTRO REALIZADO COM SUCESSO\n");
    printf("Jogador: %s\n", nome);
    printf("Apelido: %s\n", apelido);
    printf("Status: Pronto para entrar na equipe.\n");

    return 0;
}