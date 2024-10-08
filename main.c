#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define FILENAME "usuarios.txt"

// Estrutura para armazenar informações do usuário
typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

// Função para cadastrar um usuário
void cadastrarUsuario() {
    User user;
    FILE *file = fopen(FILENAME, "a"); // Abre o arquivo em modo de append

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o nome de usuario: ");
    scanf("%s", user.username);
    printf("Digite a senha: ");
    scanf("%s", user.password);

    // Salva os dados no arquivo
    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);
    printf("Usuario cadastrado com sucesso!\n");
}

// Função para fazer login
void loginUsuario() {
    User user;
    char username[USERNAME_LENGTH], password[PASSWORD_LENGTH];
    FILE *file = fopen(FILENAME, "r"); // Abre o arquivo em modo de leitura

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o nome de usuário: ");
    scanf("%s", username);
    printf("Digite a senha: ");
    scanf("%s", password);

    // Verifica se o usuário existe
    int found = 0;
    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        printf("Login bem-sucedido!\n");
    } else {
        printf("Usuário ou senha inválidos.\n");
    }
}

int main() {
    int option;

    do {
        printf("------------------");
        printf(" Cadastro / Login ");
        printf("------------------");
        printf("\n1. Cadastrar Usuario\n2. Login\n3. Sair\nEscolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                loginUsuario();
                break;
            case 3:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (option != 3);

    return 0;
}
