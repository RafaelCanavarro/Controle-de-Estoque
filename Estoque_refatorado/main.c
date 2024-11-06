#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estoque.h"

// Definindo o valor de MAX_PRODUTOS
#define MAX_PRODUTOS 100

// Função para exibir o menu principal
void exibirMenu() {
    printf("\n--- Sistema de Controle de Estoque ---\n");
    printf("1. Adicionar Produto\n");
    printf("2. Remover Produto\n");
    printf("3. Listar Produtos\n");
    printf("4. Buscar Produto\n");
    printf("5. Salvar Estoque\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para obter um número inteiro de forma segura
int obterNumeroInteiro() {
    int numero;
    while (scanf("%d", &numero) != 1) {
        printf("Entrada inválida. Tente novamente: ");
        while (getchar() != '\n');  // Limpar o buffer do teclado
    }
    return numero;
}

// Função para obter uma string do usuário de forma segura
void obterString(char *buffer, size_t tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        // Remover o caractere de nova linha, se presente
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        printf("Erro ao ler a entrada.\n");
        exit(1);
    }
}

// Função para adicionar um produto
void adicionarProdutoUI(Produto *estoque, int *quantidade) {
    int id, quantidade_adicionar;
    char nome[100];
    float preco;

    printf("Digite o ID do produto: ");
    id = obterNumeroInteiro();
    getchar();  // Limpar o buffer após ler o ID

    printf("Digite o nome do produto: ");
    obterString(nome, sizeof(nome));

    printf("Digite o preço do produto: ");
    scanf("%f", &preco);

    printf("Digite a quantidade a ser adicionada: ");
    quantidade_adicionar = obterNumeroInteiro();

    // Chama a função para adicionar o produto ao estoque
    adicionarProduto(estoque, quantidade, id, nome, preco, quantidade_adicionar);
}

// Função para remover um produto
void removerProdutoUI(Produto *estoque, int *quantidade) {
    int id;
    printf("Digite a ID do produto a ser removido: ");
    id = obterNumeroInteiro();
    removerProduto(estoque, quantidade, id);
}

// Função para buscar um produto
void buscarProdutoUI(Produto *estoque, int quantidade) {
    int id;
    printf("Digite a ID do produto para busca: ");
    id = obterNumeroInteiro();
    Produto *prod = buscarProduto(estoque, quantidade, id);
    if (prod != NULL) {
        printf("Produto encontrado: %s, Preco: %.2f, Quantidade: %d\n", prod->nome, prod->preco, prod->quantidade);
    } else {
        printf("Produto nao encontrado!\n");
    }
}

// Função para listar todos os produtos
void listarProdutosUI(Produto *estoque, int quantidade) {
    listarProdutos(estoque, quantidade);
}

// Função principal
int main() {
    Produto estoque[MAX_PRODUTOS];  // Capacidade do estoque
    int quantidade = carregarEstoque(estoque);  // Carregar estoque salvo
    int opcao;

    do {
        exibirMenu();
        opcao = obterNumeroInteiro();

        switch(opcao) {
            case 1:
                adicionarProdutoUI(estoque, &quantidade);
                break;
            case 2:
                removerProdutoUI(estoque, &quantidade);
                break;
            case 3:
                listarProdutosUI(estoque, quantidade);
                break;
            case 4:
                buscarProdutoUI(estoque, quantidade);
                break;
            case 5:
                salvarEstoque(estoque, quantidade);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}


