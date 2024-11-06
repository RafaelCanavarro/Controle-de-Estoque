#include <stdio.h>
#include <string.h>
#include "estoque.h"

#define ARQUIVO_ESTOQUE "estoque.dat"

// Função para verificar se o arquivo foi aberto com sucesso
int verificarArquivo(FILE *file) {
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }
    return 1;
}

// Função para salvar o estoque em um arquivo binário
void salvarEstoque(Produto *produtos, int quantidade) {
    FILE *file = fopen(ARQUIVO_ESTOQUE, "wb");
    if (!verificarArquivo(file)) {
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
    if (!verificarArquivo(file)) {
        return 0;
    }

    int quantidade;
    fread(&quantidade, sizeof(int), 1, file);
    fread(produtos, sizeof(Produto), quantidade, file);
    fclose(file);

    return quantidade;
}

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
