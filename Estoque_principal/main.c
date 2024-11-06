#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define ARQUIVO_ESTOQUE "estoque.dat"

// Definindo a estrutura Produto
typedef struct {
    int id;
    char nome[100];
    float preco;
    int quantidade;
} Produto;

// Função para adicionar um produto ao estoque
void adicionarProduto(Produto *produtos, int *quantidade, int id, const char *nome, float preco, int quantidade_adicionar) {
    Produto novo_produto;
    novo_produto.id = id;
    strcpy(novo_produto.nome, nome);
    novo_produto.preco = preco;
    novo_produto.quantidade = quantidade_adicionar;

    produtos[*quantidade] = novo_produto;
    (*quantidade)++;

    printf("Produto %s adicionado com sucesso!\n", nome);
}

// Função para remover um produto do estoque
void removerProduto(Produto *produtos, int *quantidade, int id) {
    int i;
    for (i = 0; i < *quantidade; i++) {
        if (produtos[i].id == id) {
            for (int j = i; j < *quantidade - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            (*quantidade)--;
            printf("Produto com ID %d removido com sucesso!\n", id);
            return;
        }
    }
    printf("Produto com ID %d nao encontrado!\n", id);
}

// Função para listar todos os produtos do estoque
void listarProdutos(Produto *produtos, int quantidade) {
    if (quantidade == 0) {
        printf("O estoque está vazio!\n");
        return;
    }

    printf("ID\tNome\tPreco\tQuantidade\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d\t%s\t%.2f\t%d\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

// Função para buscar um produto pelo ID
Produto* buscarProduto(Produto *produtos, int quantidade, int id) {
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].id == id) {
            return &produtos[i];
        }
    }
    return NULL;
}

// Função para salvar o estoque em um arquivo binário
void salvarEstoque(Produto *produtos, int quantidade) {
    FILE *file = fopen(ARQUIVO_ESTOQUE, "wb");
    if (file == NULL) {
        printf("Erro ao salvar o estoque!\n");
        return;
    }
    fwrite(&quantidade, sizeof(int), 1, file);
    fwrite(produtos, sizeof(Produto), quantidade, file);
    fclose(file);
    printf("Estoque salvo com sucesso!\n");
}

// Função para carregar o estoque do arquivo binário
int carregarEstoque(Produto *produtos) {
    FILE *file = fopen(ARQUIVO_ESTOQUE, "rb");
    if (file == NULL) {
        printf("Nao foi possível carregar o estoque!\n");
        return 0;
    }

    int quantidade;
    fread(&quantidade, sizeof(int), 1, file);
    fread(produtos, sizeof(Produto), quantidade, file);
    fclose(file);

    return quantidade;
}

int main() {
    Produto estoque[MAX_PRODUTOS];  // Capacidade do estoque
    int quantidade = carregarEstoque(estoque);  // Carregar estoque salvo
    int opcao;

    do {
        printf("\n--- Sistema de Controle de Estoque ---\n");
        printf("1. Adicionar Produto\n");
        printf("2. Remover Produto\n");
        printf("3. Listar Produtos\n");
        printf("4. Buscar Produto\n");
        printf("5. Salvar Estoque\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                int id, quantidade_adicionar;
                char nome[100];
                float preco;
                printf("Digite o ID do produto: ");
                scanf("%d", &id);
                printf("Digite o nome do produto: ");
                scanf(" %[^\n]s", nome);  // Lê a string com espaços
                printf("Digite o valor do produto: ");
                scanf("%f", &preco);
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade_adicionar);
                adicionarProduto(estoque, &quantidade, id, nome, preco, quantidade_adicionar);
                break;
            }
            case 2: {
                int id;
                printf("Digite a ID do produto a ser removido: ");
                scanf("%d", &id);
                removerProduto(estoque, &quantidade, id);
                break;
            }
            case 3:
                listarProdutos(estoque, quantidade);
                break;
            case 4: {
                int id;
                printf("Digite a ID do produto para busca: ");
                scanf("%d", &id);
                Produto *prod = buscarProduto(estoque, quantidade, id);
                if (prod != NULL) {
                    printf("Produto encontrado: %s, Preco: %.2f, Quantidade: %d\n", prod->nome, prod->preco, prod->quantidade);
                } else {
                    printf("Produto nao encontrado!\n");
                }
                break;
            }
            case 5:
                salvarEstoque(estoque, quantidade);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao nao encontrada!\n");
        }
    } while (opcao != 6);

    return 0;
}
