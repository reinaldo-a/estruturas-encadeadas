#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da página
typedef struct navegacao {
    char aba[244];
    struct navegacao *anterior;
    struct navegacao *prox;
} NO;

// Protótipos
NO *NewPage(NO *cabeca);
NO *voltar(NO *atual);
NO *proximo(NO *atual);
void historico(NO *cabeca);
NO *excluirAtual(NO *atual);

int main() {
    int opcao;
    NO cabeca;
    cabeca.prox = NULL;
    cabeca.anterior = NULL;
    NO *atual = NULL;

    do {
        system("clear");
        printf("\n===== HISTORICO DE NAVEGACAO =====\n");
        if(atual != NULL)
            printf("|| --> Pagina Atual %s <-- || \n", atual->aba);
        printf("1 - Visitar nova pagina\n");
        printf("2 - Voltar\n");
        printf("3 - Avancar\n");
        printf("4 - Historico de Navegação\n");
        printf("5 - Excluir aba atual\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1:
                system("clear");
                atual = NewPage(&cabeca);
                break;
            case 2:
                system("clear");
                atual = voltar(atual);
                break;
            case 3:
                system("clear");
                atual = proximo(atual);
                break;
            case 4:
                system("clear");
                historico(&cabeca);
                printf("Aperte Enter para continuar...");
                getchar(); // limpa \n do scanf anterior
                break;
            case 5:
                system("clear");
                atual = excluirAtual(atual);
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}

NO *NewPage(NO *cabeca) {
    NO *novo = malloc(sizeof(NO));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    printf("Digite a nova pesquisa: ");
    scanf("%s", novo->aba);
    novo->anterior = NULL;
    novo->prox = NULL;

    // se a lista estiver vazia
    if (cabeca->prox == NULL) {
        cabeca->prox = novo;
        novo->anterior = cabeca;
        return novo;
    }

    NO *atual = cabeca->prox;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = novo;
    novo->anterior = atual;

    return novo;
}

NO *voltar(NO *atual) {
    if (atual == NULL || atual->anterior == NULL || atual->anterior->anterior == NULL) {
        printf("Nao tem pagina anterior! Essa foi a primeria pesquisa.\n");
        return atual;
    }

    atual = atual->anterior;
    printf("Voce voltou para: %s\n", atual->aba);
    return atual;
}

NO *proximo(NO *atual) {
    if (atual == NULL || atual->prox == NULL) {
        printf("\nNao tem pagina seguinte! Essa era a ultima pagina.\n");
        return atual;
    }

    atual = atual->prox;
    printf("Voce avancou para: %s\n", atual->aba);
    return atual;
}

void historico(NO *cabeca) {

    if (cabeca->prox == NULL) {
        printf("Nenhuma pagina foi visitada ainda!\n");
        return;
    }
    
    printf("============= Historico ==============\n");

    NO *atual = cabeca->prox;

    int cont = 1;
    while(atual != NULL) {
        printf("Pesquisa número %i: %s\n", cont, atual->aba);
        cont ++;
        atual = atual->prox;
    }
        
    
}

NO *excluirAtual(NO *atual) {
    if (atual == NULL || atual->anterior == NULL) {
        printf("Nao ha pagina atual para excluir!\n");
        return atual;
    }

    NO *proxAba = atual->prox; // próxima aba
    NO *antAba = atual->anterior; // aba anterior

    // "excluida" a aba atual da lista
    if(antAba != NULL)
        antAba->prox = proxAba;
    if(proxAba != NULL)
        proxAba->anterior = antAba;

    printf("Aba '%s' excluida!\n", atual->aba);
    free(atual);

    // retorna a aba que ficará como atual
    if(proxAba != NULL)
        return proxAba; // se houver próxima, vai pra ela
    else if(antAba->anterior != NULL)
        return antAba;  // senão, volta para a anterior
    else
        return NULL;    // lista ficou vazia
}
