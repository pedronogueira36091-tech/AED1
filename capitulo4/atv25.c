#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char jogador[30];
    int pontuacao;
} Partida;

typedef struct {
    Partida *vetor;
    int qtd;
} Temporada;

void cadastrar(Temporada *temp) {
    Partida *novo_vetor = (Partida *)realloc(temp->vetor, (temp->qtd + 1) * sizeof(Partida));
    if (novo_vetor == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    temp->vetor = novo_vetor;
    Partida *p = &temp->vetor[temp->qtd];
    p->id = temp->qtd + 1;

    printf("Nome do jogador: ");
    getchar(); // Limpa o buffer de entrada
    fgets(p->jogador, sizeof(p->jogador), stdin);
    p->jogador[strcspn(p->jogador, "\n")] = '\0'; // Remove o \n final

    printf("Pontuacao: ");
    scanf("%d", &p->pontuacao);
    temp->qtd++;
    printf("Partida cadastrada com sucesso!\n");
}

void listar(Temporada *temp) {
    if (temp->qtd == 0) {
        printf("Nenhuma partida cadastrada.\n");
        return;
    }
    for (int i = 0; i < temp->qtd; i++) {
        printf("ID: %d | Jogador: %s | Pontos: %d\n",
               temp->vetor[i].id, temp->vetor[i].jogador, temp->vetor[i].pontuacao);
    }
}

// 1. Salvar vetor em arquivo binario (modo "wb" - sobrescrever)
void salvar_binario(const char *nome_arquivo, Temporada *temp) {
    FILE *arq = fopen(nome_arquivo, "wb"); // "wb": modo de escrita binaria (sobrescreve)
    if (arq == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    if (fwrite(&temp->qtd, sizeof(int), 1, arq) != 1) {
        printf("Erro ao gravar quantidade de elementos.\n");
        fclose(arq);
        return;
    }

    if (temp->qtd > 0) {
        size_t gravados = fwrite(temp->vetor, sizeof(Partida), temp->qtd, arq);
        if (gravados != (size_t)temp->qtd) {
            printf("Erro ao gravar dados das partidas (gravados %zu de %d).\n", gravados, temp->qtd);
        } else {
            printf("Dados salvos em binario com sucesso!\n");
        }
    }

    fclose(arq);
}

// 2. Acrescentar uma partida em arquivo binario existente (modo "ab")
void acrescentar_binario(const char *nome_arquivo, Temporada *temp) {
    if (temp->qtd == 0) return;

    FILE *arq = fopen(nome_arquivo, "ab"); // "ab": modo append binario (acrescenta ao final)
    if (arq == NULL) {
        perror("Erro ao abrir arquivo para acrescentar");
        return;
    }

    // Grava apenas o ultimo elemento adicionado
    fwrite(&temp->vetor[temp->qtd - 1], sizeof(Partida), 1, arq);
    fclose(arq);
    printf("Ultima partida acrescentada ao arquivo binario.\n");
}

// 3. Carregar vetor de arquivo binario (modo "rb" e verificacao de arquivo inexistente/erros)
void carregar_binario(const char *nome_arquivo, Temporada *temp) {
    FILE *arq = fopen(nome_arquivo, "rb"); // "rb": modo de leitura binaria
    if (arq == NULL) {
        // Trata o caso de arquivo inexistente ou erro de permissao
        printf("Aviso: O arquivo '%s' nao existe ou nao pôde ser aberto.\n", nome_arquivo);
        return;
    }

    int nova_qtd;
    if (fread(&nova_qtd, sizeof(int), 1, arq) != 1) {
        if (feof(arq)) {
            printf("Fim de arquivo alcancado inesperadamente ao ler quantidade.\n");
        } else if (ferror(arq)) {
            printf("Erro de leitura no arquivo.\n");
        }
        fclose(arq);
        return;
    }

    Partida *temp_vetor = (Partida *)malloc(nova_qtd * sizeof(Partida));
    if (temp_vetor == NULL) {
        printf("Erro de alocacao de memoria!\n");
        fclose(arq);
        return;
    }

    size_t lidos = fread(temp_vetor, sizeof(Partida), nova_qtd, arq);
    if (lidos != (size_t)nova_qtd) {
        if (feof(arq)) {
            printf("Fim de arquivo encontrado antes de ler todos os dados esperados.\n");
        }
        if (ferror(arq)) {
            printf("Ocorreu um erro de leitura no arquivo.\n");
        }
        free(temp_vetor);
        fclose(arq);
        return;
    }

    fclose(arq);

    free(temp->vetor);
    temp->vetor = temp_vetor;
    temp->qtd = nova_qtd;
    printf("Dados carregados com sucesso do arquivo binario!\n");
}

// 4. Exportar/converter para arquivo de texto (modo "w")
void exportar_texto(const char *nome_arquivo, Temporada *temp) {
    FILE *arq = fopen(nome_arquivo, "w"); // "w": modo de escrita em texto (sobrescreve)
    if (arq == NULL) {
        perror("Erro ao criar arquivo de texto");
        return;
    }

    fprintf(arq, "ID;Jogador;Pontuacao\n");
    for (int i = 0; i < temp->qtd; i++) {
        fprintf(arq, "%d;%s;%d\n", temp->vetor[i].id, temp->vetor[i].jogador, temp->vetor[i].pontuacao);
    }

    fclose(arq);
    printf("Dados exportados para texto (%s) com sucesso!\n", nome_arquivo);
}

int main() {
    Temporada temp = {NULL, 0};
    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Cadastrar partida\n");
        printf("2. Listar partidas\n");
        printf("3. Salvar em binario (wb)\n");
        printf("4. Carregar de binario (rb)\n");
        printf("5. Acrescentar ultima partida em binario (ab)\n");
        printf("6. Exportar para arquivo de texto (w)\n");
        printf("7. Testar abertura de arquivo inexistente\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar(&temp);
                break;
            case 2:
                listar(&temp);
                break;
            case 3:
                salvar_binario("temporada.bin", &temp);
                break;
            case 4:
                carregar_binario("temporada.bin", &temp);
                break;
            case 5:
                acrescentar_binario("temporada.bin", &temp);
                break;
            case 6:
                exportar_texto("temporada.txt", &temp);
                break;
            case 7:
                carregar_binario("arquivo_que_nao_existe.bin", &temp);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    free(temp.vetor);
    return 0;
}