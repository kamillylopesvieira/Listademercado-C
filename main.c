#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// estrutura para itens
typedef struct {
    char nome[15];
    float preco;
    int quantidade;
} Produtos;

// estrutura da lista
typedef struct {
    int tipo;
    Produtos *itens;
    int tamanho;
} Lista;


// função de pausa
void pausar(){
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
    getchar();
}


// função para listar itens
void listar(Lista lista){

    if(lista.tamanho == 0){
        printf("Nao ha itens na lista.\n");
        return;
    }

    printf("\nItens da lista:\n");

    for(int i = 0; i < lista.tamanho; i++){

        printf("\nItem %d\n", i+1);
        printf("Nome: %s\n", lista.itens[i].nome);
        printf("Preco: %.2f\n", lista.itens[i].preco);
        printf("Quantidade: %d\n", lista.itens[i].quantidade);
    }
}


// função para criar lista
Lista criarLista(){

    Lista lista;

    printf("Qual tipo de lista deseja criar?\n");
    printf("1 - Comida\n");
    printf("2 - Limpeza\n");
    printf("3 - Roupa\n");
    scanf("%d", &lista.tipo);

    printf("Quantos itens deseja adicionar? ");
    scanf("%d", &lista.tamanho);

    lista.itens = (Produtos*) malloc(lista.tamanho * sizeof(Produtos));

    for(int i = 0; i < lista.tamanho; i++){

        printf("\nProduto %d\n", i+1);

        printf("Nome: ");
        scanf("%s", lista.itens[i].nome);

        printf("Preco: ");
        scanf("%f", &lista.itens[i].preco);

        printf("Quantidade: ");
        scanf("%d", &lista.itens[i].quantidade);
    }

    return lista;
}


// função editar
void editar(Lista *lista){

    int indice;

    if(lista->tamanho == 0){
        printf("Nao ha itens para editar.\n");
        return;
    }

    listar(*lista);

    printf("\nDigite o numero do item para editar: ");
    scanf("%d", &indice);

    if(indice < 1 || indice > lista->tamanho){
        printf("Opcao invalida!\n");
        return;
    }

    indice--;

    printf("Novo nome: ");
    scanf("%s", lista->itens[indice].nome);

    printf("Novo preco: ");
    scanf("%f", &lista->itens[indice].preco);

    printf("Nova quantidade: ");
    scanf("%d", &lista->itens[indice].quantidade);

    printf("Item editado com sucesso.\n");
}


// função remover
void remover(Lista *lista){

    int indice;

    if(lista->tamanho == 0){
        printf("Nao ha itens para remover.\n");
        return;
    }

    listar(*lista);

    printf("\nDigite o numero do item para remover: ");
    scanf("%d", &indice);

    if(indice < 1 || indice > lista->tamanho){
        printf("Opcao invalida!\n");
        return;
    }

    indice--;

    for(int i = indice; i < lista->tamanho - 1; i++){
        lista->itens[i] = lista->itens[i+1];
    }

    lista->tamanho--;

    printf("Item removido com sucesso.\n");
}


int main(){

    Lista lista;
    lista.tamanho = 0;
    lista.itens = NULL;

    int listaCriada = 0;
    int opcao;

    do{

        printf("\nMENU\n");
        printf("1 - Criar lista\n");
        printf("2 - Listar itens\n");
        printf("3 - Editar item\n");
        printf("4 - Remover item\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &opcao);

        switch(opcao){

            case 1:

                if(listaCriada){
                    free(lista.itens);
                }

                lista = criarLista();
                listaCriada = 1;
                break;

            case 2:

                if(!listaCriada){
                    printf("Nenhuma lista criada ainda.\n");
                    pausar();
                    break;
                }

                listar(lista);
                pausar();
                break;

            case 3:

                if(!listaCriada){
                    printf("Nenhuma lista criada ainda.\n");
                    pausar();
                    break;
                }

                editar(&lista);
                pausar();
                break;

            case 4:

                if(!listaCriada){
                    printf("Nenhuma lista criada ainda.\n");
                    pausar();
                    break;
                }

                remover(&lista);
                pausar();
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                pausar();
        }

    }while(opcao != 0);

    if(listaCriada){
        free(lista.itens);
    }

    return 0;
}
