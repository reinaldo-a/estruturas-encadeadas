#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da música (lista duplamente circular)
typedef struct NO {
    char nome[244];
    struct NO *prox;
    struct NO *ant;
} NO;

// Protótipos
void AdicionarMusica(NO *cabeca);
void ListarMusicas(NO *cabeca);
void RemoverMusica(NO *cabeca);

int main() {
    int opcao;
    NO *cabeca = NULL; // lista inicialmente vazia
    NO *atual = NULL;  // música que está tocando

    do {
        printf("\n=== PLAYLIST ===\n");
        if (atual)
            printf("Música atual: %s\n", atual->nome);
        else
            printf("Playlist vazia!\n");

        printf("------------------------\n");
        printf("1. Adicionar Música\n");
        printf("2. Remover Música\n");
        printf("3. Próxima Música\n");
        printf("4. Música Anterior\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1:
                system("clear");
                if (!cabeca) {
                    // primeira música
                    cabeca = malloc(sizeof(NO));
                    if (!cabeca) {
                        printf("Erro ao alocar memória!\n");
                        break;
                    }
                    printf("Digite o nome da música: ");
                    scanf(" %[^\n]", cabeca->nome);
                    cabeca->prox = cabeca->ant = cabeca;
                    atual = cabeca;
                    printf("Música '%s' adicionada à playlist!\n", cabeca->nome);
                } else {
                    AdicionarMusica(cabeca);
                }
                break;

            case 2:
                system("clear");
                if (cabeca)
                    RemoverMusica(cabeca);
                else
                    printf("Playlist vazia! Nada para remover.\n");
                break;

            case 3:
                system("clear");
                if (atual)
                    atual = atual->prox, printf("Próxima música: %s\n", atual->nome);
                else
                    printf("Playlist vazia!\n");
                break;

            case 4:
                system("clear");
                if (atual)
                    atual = atual->ant, printf("Música anterior: %s\n", atual->nome);
                else
                    printf("Playlist vazia!\n");
                break;

            case 5:
                printf("Encerrando a playlist...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    // libera memória
    if (cabeca) {
        NO *aux = cabeca->prox;
        while (aux != cabeca) {
            NO *temp = aux;
            aux = aux->prox;
            free(temp);
        }
        free(cabeca);
    }

    return 0;
}

// Adiciona música no final da lista
void AdicionarMusica(NO *cabeca) {
    NO *nova = malloc(sizeof(NO));
    if (!nova) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    printf("Digite o nome da música: ");
    scanf(" %[^\n]", nova->nome);

    NO *ultima = cabeca->ant;
    ultima->prox = nova;
    nova->ant = ultima;
    nova->prox = cabeca;
    cabeca->ant = nova;

    printf("Música '%s' adicionada à playlist!\n", nova->nome);
}

// Remove uma música da playlist
void RemoverMusica(NO *cabeca) {
    char remover[244];
    printf("Digite o nome da música a remover: ");
    scanf(" %[^\n]", remover);

    NO *atual = cabeca;

    do {
        if (strcmp(atual->nome, remover) == 0) {
            if (atual->prox == atual) {
                // última música
                free(atual);
                printf("Playlist ficou vazia!\n");
            } else {
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
                if (cabeca == atual)
                    cabeca = atual->prox;
                free(atual);
            }
            printf("Música '%s' removida!\n", remover);
            return;
        }
        atual = atual->prox;
    } while (atual != cabeca);

    printf("Música '%s' não encontrada na playlist.\n", remover);
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