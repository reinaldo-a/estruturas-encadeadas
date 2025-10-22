// circular simples: Rota do onibus
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da página
typedef struct ponto {
    char nome[244];
    struct ponto *prox;
} NO;

// Protótipos
void AdicionarPonto(NO *cabeca);
void Listar(NO *cabeca);
void RemoverPonto(NO *cabeca);

int main() {
    int opcao;
    NO *cabeca = malloc(sizeof(NO)); 
    if (cabeca == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    strcpy(cabeca->nome, "Centro");  // ponto inicial fixo
    cabeca->prox = cabeca;           // aponta pra si mesmo (lista circular)

    NO *atual = cabeca; // começa no "Centro"

    do {
        printf("\n=== ROTA DO ÔNIBUS ===\n");
        printf("Ponto atual: %s\n", atual->nome);
        printf("------------------------\n");
        printf("1. Adicionar Ponto\n");
        printf("2. Listar Pontos\n");
        printf("3. Remover Ponto\n");
        printf("4. Próximo Ponto\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1:
                system("clear");
                AdicionarPonto(cabeca);
                break;

            case 2:
                system("clear");
                Listar(cabeca);
                break;

            case 3:
                system("clear");
                RemoverPonto(cabeca);
                break;

            case 4:
                system("clear");
                atual = atual->prox;
                printf("Ônibus foi para o próximo ponto!\n");
                printf("Agora está em: %s\n", atual->nome);
                break;

            case 5:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    // libera memória no final
    NO *aux = cabeca->prox;
    while (aux != cabeca) {
        NO *temp = aux;
        aux = aux->prox;
        free(temp);
    }
    free(cabeca);

    return 0;
}

void AdicionarPonto(NO *cabeca) {
    NO *novo = malloc(sizeof(NO));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    printf("Digite o nome do novo ponto: ");
    scanf("%s", novo->nome);

    // insere no final, antes de voltar pro Centro
    NO *aux = cabeca;
    while (aux->prox != cabeca) {
        aux = aux->prox;
    }

    aux->prox = novo;
    novo->prox = cabeca;

    printf("Ponto '%s' adicionado à rota!\n", novo->nome);
}

void Listar(NO *cabeca) {
    NO *aux = cabeca;
    printf("=== Pontos da Rota ===\n");

    do {
        printf("- %s\n", aux->nome);
        aux = aux->prox;
    } while (aux != cabeca);

    printf("======================\n");
}

void RemoverPonto(NO *cabeca) {
    char remover[244];
    printf("Digite o nome do ponto a remover: ");
    scanf("%s", remover);

    if (strcmp(remover, "Centro") == 0) {
        printf("O ponto 'Centro' não pode ser removido!\n");
        return;
    }

    NO *anterior = cabeca;
    NO *atual = cabeca->prox;

    while (atual != cabeca) {
        if (strcmp(atual->nome, remover) == 0) {
            anterior->prox = atual->prox;
            free(atual);
            printf("Ponto '%s' removido com sucesso!\n", remover);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Ponto '%s' não encontrado na rota.\n", remover);
}
