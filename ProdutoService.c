#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Produto{ //Estrutura para variaveis que formam produtos
    int id;
    char nome[50];
    float valor;
    int quantidade;
};

// Função para verificar se o ID já existe no arquivo
int idJaExiste(int id) {
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        return 0; // Arquivo não existe, ID não existe
    }

    struct Produto p;
    while (fscanf(arquivo, "%d,%49[^,],%f,%d", &p.id, p.nome, &p.valor, &p.quantidade) != EOF) {
        if (p.id == id) {
            fclose(arquivo);
            return 1; // ID encontrado
        }
    }

    fclose(arquivo);
    return 0; // ID não encontrado
}

// Função para verificar se o nome já existe
int nomeJaExiste(char *nome) {
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        return 0; // Arquivo não existe, nome não existe
    }

    struct Produto p;
    while (fscanf(arquivo, "%d,%49[^,],%f,%d", &p.id, p.nome, &p.valor, &p.quantidade) != EOF) {
        if (strcmp(p.nome, nome) == 0) {
            fclose(arquivo);
            return 1; // Nome encontrado
        }
    }

    fclose(arquivo);
    return 0; // Nome não encontrado
}

// Função para gerar um número aleatório único para o ID
int gerarnum() {
    int id;
    do {
        id = rand() % 100 + 1; // Gera um número aleatório entre 1 e 100
    } while (idJaExiste(id)); // Verifica se o ID já existe
    return id;
}

// Função para cadastrar o produto
void CadastrarProduto() {
    FILE *arquivo = fopen("produtos.txt", "a"); // Abre o arquivo no modo de adição
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    struct Produto p;
    // Adicionar as informações do produto
    printf("Digite o nome do produto: ");
    scanf("%s", p.nome);

    if (nomeJaExiste(p.nome)) {
        printf("Erro: Produto com este nome já existe!\n");
        fclose(arquivo);
        return;
    }

    p.id = gerarnum();
    printf("Código do produto = %d\n", p.id);
    printf("Digite o valor do produto: ");
    scanf("%f", &p.valor);
    printf("Digite a quantidade dos produtos: ");
    scanf("%d", &p.quantidade);

    // Grava os dados no arquivo e adiciona uma nova linha no final
    fprintf(arquivo, "%d,%s,%.2f,%d\n", p.id, p.nome, p.valor, p.quantidade);
    printf("Produto Cadastrado!\n");

    fclose(arquivo); // Fecha o arquivo corretamente
}

void ListarProduto() {
    FILE *arquivo = fopen("produtos.txt", "r");  // Abre o arquivo no modo de leitura
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo ou arquivo não encontrado!\n");
        return;
    }

    struct Produto p;
    printf("\n--- LISTA DE PRODUTOS ---\n");

    // Lê cada linha do arquivo e exibe as informações do produto
    while (fscanf(arquivo, "%d,%49[^,],%f,%d\n", &p.id, p.nome, &p.valor, &p.quantidade) == 4) {
        printf("ID: %d\n", p.id);
        printf("Nome: %s\n", p.nome);
        printf("Valor: R$ %.2f\n", p.valor);
        printf("Quantidade: %d\n", p.quantidade);
        printf("------------------------\n");
    }

    fclose(arquivo);  // Fecha o arquivo após leitura
    
}

void EditarProduto() {
    FILE *arquivo = fopen("produtos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");  // Arquivo temporário para reescrever os produtos

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int idProduto, encontrado = 0;
    struct Produto p;

    printf("Digite o ID do produto que deseja editar: ");
    scanf("%d", &idProduto);

    // Lê cada produto do arquivo
    while (fscanf(arquivo, "%d,%[^,],%f,%d\n", &p.id, p.nome, &p.valor, &p.quantidade) != EOF) {
        if (p.id == idProduto) {
            encontrado = 1;
            int opcao;
            printf("Produto encontrado: %s (R$%.2f, %d unidades)\n", p.nome, p.valor, p.quantidade);
            
            printf("O que deseja editar?\n");
            printf("1. Nome\n2. Preço\n3. Quantidade\nEscolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf("%s", p.nome);
                    break;
                case 2:
                    printf("Digite o novo preco: ");
                    scanf("%f", &p.valor);
                    break;
                case 3:
                    printf("Digite a nova quantidade: ");
                    scanf("%d", &p.quantidade);
                    break;
                default:
                    printf("Opção invalida!\n");
                    break;
            }

            printf("Produto atualizado!\n");
        }
        // Grava o produto (alterado ou não) no arquivo temporário
        fprintf(temp, "%d,%s,%.2f,%d\n", p.id, p.nome, p.valor, p.quantidade);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Produto com ID %d não encontrado.\n", idProduto);
    } else {
        // Substitui o arquivo original pelo temporário
        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");
    }
}

void MostrarProdutos() {
    struct Produto produto;
    FILE *arquivo;
    
    arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Lista de Produtos:\n");
    while (fscanf(arquivo, "%d,%49[^,],%f,%d", &produto.id, produto.nome, &produto.valor, &produto.quantidade) != EOF) {
        printf("ID: %d, Nome: %s, Valor: R$%.2f, Quantidade: %d\n", produto.id, produto.nome, produto.valor, produto.quantidade);
    }

    fclose(arquivo);
}


void Balanca() {
    struct Produto produto;
    FILE *arquivo;
    FILE *temp;
    int quantidadeDesejada;
    int idProduto, encontrado = 0;
    float total = 0.0;
    char continuar;

    // Mostrar lista de produtos
    MostrarProdutos();

    do {
        // Abre o arquivo para leitura
        arquivo = fopen("produtos.txt", "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return;
        }

        // Abre o arquivo temporário para escrita
        temp = fopen("temp.txt", "w");
        if (temp == NULL) {
            printf("Erro ao abrir o arquivo temporário!\n");
            fclose(arquivo);
            return;
        }

        // Solicita o ID do produto e a quantidade desejada
        printf("Digite o ID do produto que deseja comprar: ");
        scanf("%d", &idProduto);
        printf("Digite a quantidade desejada: ");
        scanf("%d", &quantidadeDesejada);

        // Lê os dados do arquivo e calcula o valor total
        while (fscanf(arquivo, "%d,%49[^,],%f,%d", &produto.id, produto.nome, &produto.valor, &produto.quantidade) != EOF) {
            if (produto.id == idProduto) {
                encontrado = 1;
                if (produto.quantidade >= quantidadeDesejada) {
                    total += quantidadeDesejada * produto.valor;
                    produto.quantidade -= quantidadeDesejada;
                } else {
                    printf("Quantidade em estoque insuficiente para %s!\n", produto.nome);
                    fclose(arquivo);
                    fclose(temp);
                    remove("temp.txt");
                    return;
                }
            }
            fprintf(temp, "%d,%s,%.2f,%d\n", produto.id, produto.nome, produto.valor, produto.quantidade);
        }

        fclose(arquivo);
        fclose(temp);

        // Substitui o arquivo original pelo arquivo temporário
        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");

        printf("Deseja comprar mais algum produto? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's');

    printf("Total a pagar: R$%.2f\n", total);

    if (!encontrado) {
        printf("Produto(s) não encontrado(s)!\n");
    }
}
