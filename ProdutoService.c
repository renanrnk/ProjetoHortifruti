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
bool idJaExiste(int id) {
    FILE *arquivo = fopen("produtos.txt", "r");  // Abre o arquivo para leitura
    if (arquivo == NULL) {
        return false;  // Arquivo não existe ou erro ao abrir, então o ID é novo
    }

    int idExistente;
    while (fscanf(arquivo, "%d,%*[^,],%*f,%*d\n", &idExistente) != EOF) {
        if (id == idExistente) {
            fclose(arquivo);
            return true;  // O ID já existe no arquivo
        }
    }

    fclose(arquivo);
    return false;  // ID não encontrado, é novo
}

//Função para gerar numeros aleatorios para os identificadores de produto.
int gerarnum(){

    int id;
    
    do{
        return (rand() % 100 + 1); //Gera um numero aleatorio entre 1 e 100
    } while(idJaExiste(id));// Verifica se o ID ja existe
    
    return id;
}

void CadastrarProduto() {
    FILE *arquivo = fopen("produtos.txt", "a");  // Abre o arquivo no modo de adição

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    struct Produto p;

    // Adicionar as informações do produto
    printf("Digite o nome do produto: ");
    scanf("%s", p.nome);

    p.id = gerarnum();
    printf("Codigo do produto = %d\n", p.id);

    printf("Digite o valor do produto: ");
    scanf("%f", &p.valor);

    printf("Digite a quantidade dos produtos: ");
    scanf("%d", &p.quantidade);

    // Grava os dados no arquivo e adiciona uma nova linha no final
    fprintf(arquivo, "%d,%s,%.2f,%d\n", p.id, p.nome, p.valor, p.quantidade);
    printf("Produto Cadastrado!\n");

    fclose(arquivo);  // Fecha o arquivo corretamente
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