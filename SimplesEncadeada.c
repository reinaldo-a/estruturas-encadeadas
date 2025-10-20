#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct filaCarro {
    char cliente[244];
    char veiculo[244];
    int ano;
    struct filaCarro *prox;
};

typedef struct filaCarro No;

// Protótipos
void adicionar(No *cabeca);
void listar(No *cabeca);
void buscar(No *cabeca, char *nome);
void atender(No *cabeca, int posicao);

int main() {
    No cabeca;
    cabeca.prox = NULL;

    int opcao = -1;
    do {
        printf("\n==============================\n");
        printf("|   SISTEMA MECANICA (FILA)  |\n");
        printf("==============================\n");
        printf("| 1. Adicionar carro         |\n");
        printf("| 2. Atender carro           |\n");
        printf("| 3. Buscar carro            |\n");
        printf("| 4. Listar fila             |\n");
        printf("| 0. Sair                    |\n");
        printf("==============================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n======================== Adicionar um carro ========================\n");
                adicionar(&cabeca);
                break;
            case 2:
                printf("\n======================== Atender carro ========================\n");
                int posicao;
                printf("qual carro será atendido?");
                scanf("%i", &posicao);
                atender(&cabeca, posicao);
                break;
            case 3: {
                printf("======================== Buscar carro ========================\n");
                char nome[244];
                printf("Digite o nome do cliente: ");
                scanf("%s", nome);
                buscar(&cabeca, nome);
                break;
            }
            case 4:
                system("clear");
                printf("======================== Listando fila de carros ========================\n");
                listar(&cabeca);
                break;
        }

        printf("Aperte Enter para continuar...");
        getchar(); // limpa \n do scanf anterior
        getchar(); // espera o Enter

    } while (opcao != 0);

    return 0;
}

// Adicionar carro
void adicionar(No *cabeca) {
    No *atual = cabeca;

    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }

    printf("Digite o nome do cliente: ");
    scanf("%s", novo->cliente);
    printf("Digite o nome do veículo: ");
    scanf("%s", novo->veiculo);
    printf("Digite o ano do %s: ", novo->veiculo);
    scanf("%d", &novo->ano);

    novo->prox = NULL;

    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;

    printf("Veículo cadastrado com sucesso!\n");
}

// Listar fila
void listar(No *cabeca) {
    No *novo = cabeca->prox;
    if (novo == NULL) {
        printf("Nenhum carro na fila.\n");
        return;
    }

    while (novo != NULL) {
        printf("Cliente: %s\nVeículo: %s - %d\n", novo->cliente, novo->veiculo, novo->ano);
        printf("==================================\n");
        novo = novo->prox;
    }
}

// Buscar cliente pelo nome
void buscar(No *cabeca, char *nome) {
    No *atual = cabeca->prox;
    int contador = 1;

    while (atual != NULL) {
        if (strcmp(atual->cliente, nome) == 0) {
            printf("%s está na posição %d da fila.\n", nome, contador);
            return;
        }
        contador++;
        atual = atual->prox;
    }

    printf("%s não está na fila.\n", nome);
}

//Atender carro e retiralo  da lista
void atender(No *cabeca, int posicao) {
    if (cabeca->prox == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    No *anterior = cabeca;
    No *atual = cabeca->prox;
    int contador = 1;

    while (atual != NULL && contador < posicao) {
        anterior = atual;
        atual = atual->prox;
        contador++;
    }

    if (atual == NULL) {
        printf("Posição inválida!\n");
        return;
    }

    anterior->prox = atual->prox;

    printf("Carro de %s (%s - %d) removido da fila.\n",
           atual->cliente, atual->veiculo, atual->ano);

    free(atual);
}