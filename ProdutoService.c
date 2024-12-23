#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Produto {
    int id;
    char nome[50];
    float valor;
    float quantidade;
};

int idJaExiste(int id) {
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        return 0; // Arquivo não existe, ID não existe
    }

    struct Produto p;
    // Verifica a leitura de todos os campos da estrutura Produto
    while (fscanf(arquivo, "%d,%49[^,],%f,%f\n", &p.id, p.nome, &p.valor, &p.quantidade) == 4) {
        if (p.id == id) {
            fclose(arquivo);
            return 1; // ID encontrado
        }
    }

    fclose(arquivo);
    return 0; // ID não encontrado
}

int nomeJaExiste(const char *nome) {
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        return 0; // Se não conseguir abrir o arquivo, consideramos que o nome não existe
    }
    
    struct Produto p;
    while (fscanf(arquivo, "%d,%49[^,],%f,%f", &p.id, p.nome, &p.valor, &p.quantidade) == 4) {
        if (strcmp(p.nome, nome) == 0) {
            fclose(arquivo);
            return 1; // Nome já existe
        }
    }

    fclose(arquivo);
    return 0; // Nome não existe
}

float lerQuantidade() {
    char input[20];
    float quantidade;
    int valido;

    do {
        printf("Digite a quantidade desejada: ");
        fgets(input, sizeof(input), stdin);

        // Remove o newline no final, se existir
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Tenta converter a entrada para float
        valido = sscanf(input, "%f", &quantidade) == 1;

        if (!valido || quantidade <= 0) {
            printf("Erro: Digite uma quantidade válida.\n");
        }
    } while (!valido || quantidade <= 0);

    return quantidade;
}

int gerarnum() {
    int id;
    do {
        id = rand() % 100 + 1; // Gera um número aleatório entre 1 e 100
    } while (idJaExiste(id)); // Verifica se o ID já existe
    return id;
}

int validarNome(char *nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            return 0; // Retorna falso se encontrar um caractere que não é letra ou espaço
        }
    }
    return 1; // Retorna verdadeiro se todos os caracteres forem letras ou espaços
}

float lerNumero(char *mensagem) {
    float numero;
    char buffer[50];
    int valido;

    do {
        printf("%s", mensagem);
        fgets(buffer, sizeof(buffer), stdin);

        // Tenta converter a entrada para float
        valido = sscanf(buffer, "%f", &numero) == 1;

        if (!valido) {
            printf("Erro: Digite apenas números.\n");
        }
    } while (!valido);

    return numero;
}

void CadastrarProduto() {
    FILE *arquivo = fopen("produtos.txt", "a"); // Abre o arquivo no modo de adição
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    struct Produto p;

    // Adicionar as informações do produto
    while (1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada

        printf("Digite o nome do produto: ");
        fgets(p.nome, sizeof(p.nome), stdin); // Usa fgets para ler o nome

        // Remove o newline no final, se existir
        size_t len = strlen(p.nome);
        if (len > 0 && p.nome[len - 1] == '\n') {
            p.nome[len - 1] = '\0';
        }

        // Verifica se o nome contém apenas letras e se já existe
        if (!validarNome(p.nome)) {
            printf("Erro: O nome deve conter apenas letras. Aperte ENTER e digite novamente.\n");
        } else if (nomeJaExiste(p.nome)) {
            printf("Erro: Produto com este nome já existe! Aperte ENTER e digite novamente.\n");
        } else {
            break; // Nome válido, sai do loop
        }
    }

    p.id = gerarnum();
    printf("Código do produto = %d\n", p.id);

    // Lê e valida o valor do produto
    p.valor = lerNumero("Digite o valor do produto: ");

    // Lê e valida a quantidade do produto
    p.quantidade = lerNumero("Digite a quantidade dos produtos: ");

    // Grava os dados no arquivo e adiciona uma nova linha no final
    fprintf(arquivo, "%d,%s,%.2f,%.2f\n", p.id, p.nome, p.valor, p.quantidade);

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
    while (fscanf(arquivo, "%d,%49[^,],%f,%f\n", &p.id, p.nome, &p.valor, &p.quantidade) == 4) {
        printf("ID: %d\n", p.id);
        printf("Nome: %s\n", p.nome);
        printf("Valor: R$ %.2f\n", p.valor);
        printf("Quantidade: %.2f\n", p.quantidade); // Mantido como float
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

    MostrarProdutos(); // Exibe a lista de produtos

    int idProduto, encontrado = 0;
    struct Produto p;

    printf("Digite o ID do produto que deseja editar: ");
    scanf("%d", &idProduto);

    // Lê cada produto do arquivo
    while (fscanf(arquivo, "%d,%49[^,],%f,%f\n", &p.id, p.nome, &p.valor, &p.quantidade) == 4) {
        if (p.id == idProduto) {
            encontrado = 1;
            int opcao;
            printf("Produto encontrado: %s (R$%.2f, %.2f unidades)\n", p.nome, p.valor, p.quantidade);
            
            printf("O que deseja editar?\n");
            printf("1. Nome\n2. Preço\n3. Quantidade\nEscolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf("%s", p.nome);
                    break;
                case 2:
                    printf("Digite o novo preço: ");
                    scanf("%f", &p.valor);
                    break;
                case 3:
                    printf("Digite a nova quantidade: ");
                    scanf("%f", &p.quantidade); // Mantenha como float
                    break;
                default:
                    printf("Opção inválida!\n");
                    break;
            }

            printf("Produto atualizado!\n");
        }
        // Grava o produto (alterado ou não) no arquivo temporário
        fprintf(temp, "%d,%s,%.2f,%.2f\n", p.id, p.nome, p.valor, p.quantidade);
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
    // Alterado para aceitar a leitura de quantidade como float
    while (fscanf(arquivo, "%d,%49[^,],%f,%f", &produto.id, produto.nome, &produto.valor, &produto.quantidade) != EOF) {
        printf("ID: %d, Nome: %s, Valor: R$%.2f, Quantidade: %.2f\n", produto.id, produto.nome, produto.valor, produto.quantidade);
    }

    fclose(arquivo);
}

void Balanca() {
    struct Produto produto;
    FILE *arquivo;
    FILE *temp;
    float quantidadeDesejada;
    int idProduto, encontrado = 0;
    float total = 0.0;
    char continuar;

    // Buffer para o cupom de venda
    char cupom[1000] = "----- Cupom de Venda -----\n"; 
    char linha[100]; // Buffer para cada linha do cupom

    do {
        MostrarProdutos(); // Mostra a lista de produtos

        // Solicita o ID do produto e verifica se ele existe no arquivo
        while (1) {
            printf("Digite o ID do produto que deseja comprar: ");
            scanf("%d", &idProduto);
            while (getchar() != '\n'); // Limpa o buffer de entrada

            if (idJaExiste(idProduto)) {
                break; // ID válido, sai do loop
            } else {
                printf("Erro: ID do produto não encontrado. Tente novamente.\n");
            }
        }

        // Solicita e valida a quantidade desejada
        while (1) {
            printf("Digite a quantidade desejada: ");
            if (scanf("%f", &quantidadeDesejada) == 1 && quantidadeDesejada > 0) {
                break; // Quantidade válida, sai do loop
            } else {
                printf("Erro: Digite uma quantidade válida.\n");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            }
        }

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

        // Lê os dados do arquivo e processa a compra
        while (fscanf(arquivo, "%d,%49[^,],%f,%f\n", &produto.id, produto.nome, &produto.valor, &produto.quantidade) == 4) {
            if (produto.id == idProduto) {
                encontrado = 1;
                if (produto.quantidade >= quantidadeDesejada) {
                    float valorItem = quantidadeDesejada * produto.valor;
                    total += valorItem;
                    produto.quantidade -= quantidadeDesejada;

                    // Adiciona a linha do produto ao cupom
                    sprintf(linha, "Produto: %s | Quantidade: %.2f | Preço: R$%.2f\n", produto.nome, quantidadeDesejada, valorItem);
                    strcat(cupom, linha);
                } else {
                    printf("Quantidade em estoque insuficiente para %s!\n", produto.nome);
                    fclose(arquivo);
                    fclose(temp);
                    remove("temp.txt");
                    return;
                }
            }
            fprintf(temp, "%d,%s,%.2f,%.2f\n", produto.id, produto.nome, produto.valor, produto.quantidade);
        }

        fclose(arquivo);
        fclose(temp);

        // Substitui o arquivo original pelo temporário
        remove("produtos.txt");
        rename("temp.txt", "produtos.txt");

        printf("Deseja comprar mais algum produto? (s/n): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n'); // Limpa o buffer de entrada

    } while (continuar == 's');

    if (encontrado) {
        // Adiciona o total ao cupom e exibe o cupom de venda
        sprintf(linha, "Total a pagar: R$%.2f\n", total);
        strcat(cupom, linha);
        strcat(cupom, "--------------------------\n");

        printf("%s", cupom);
    } else {
        printf("Produto(s) não encontrado(s)!\n");
    }
}
