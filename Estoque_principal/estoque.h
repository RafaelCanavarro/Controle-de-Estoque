#ifndef ESTOQUE_H
#define ESTOQUE_H

// Definindo a estrutura Produto
typedef struct {
    int id;
    char nome[100];
    float preco;
    int quantidade;
} Produto;

// Funções para manipular o estoque
void adicionarProduto(Produto *produtos, int *quantidade, int id, const char *nome, float preco, int quantidade_adicionar);
void removerProduto(Produto *produtos, int *quantidade, int id);
void listarProdutos(Produto *produtos, int quantidade);
Produto* buscarProduto(Produto *produtos, int quantidade, int id);
void salvarEstoque(Produto *produtos, int quantidade);
int carregarEstoque(Produto *produtos);

#endif // ESTOQUE_H
