#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SENHA_ADMIN "admin123"


typedef struct {
    char nome[50];
    char email[50];
    char senha[50];
    int isAdmin;
} Usuario;



void MascararSenha(char *senha, const char *mensagem) {
    char ch;
    int i = 0;

    printf("%s", mensagem); // Exibe a mensagem passada como parâmetro
    while ((ch = getch()) != '\r') { // Pressione Enter para finalizar
        if (ch == '\b') { // Se pressionar Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Apaga o último caractere
            }
        } else {
            senha[i++] = ch; // Adiciona o caractere
            printf("*"); // Exibe um asterisco
        }
    }
    senha[i] = '\0'; // Termina a string
    printf("\n");
}

void CadastrarUsuario() {
    char senhaAdmin[50];
    Usuario usuario;
    FILE *arquivo;
    char emailExistente[50], senhaExistente[50], nomeExistente[50];
    int isAdminExistente;
    int emailJaExiste = 0;

    // Lê o nome do usuário
    printf("Digite o nome do usuario: ");
    scanf(" %[^\n]", usuario.nome);  // Lê o nome com espaços

    // Lê o email do usuário
    printf("Digite o email do usuario: ");
    scanf("%s", usuario.email);

    // Verifica se o e-mail já existe
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo != NULL) {
        while (fscanf(arquivo, "%s %s %s %d", nomeExistente, emailExistente, senhaExistente, &isAdminExistente) != EOF) {
            if (strcmp(emailExistente, usuario.email) == 0) {
                printf("Erro: Email ja cadastrado!\n");
                emailJaExiste = 1;
                break;
            }
        }
        fclose(arquivo);  // Não esqueça de fechar o arquivo
    }

    if (emailJaExiste) {
        return;
    }

    // Lê a senha do usuário
    
    MascararSenha(usuario.senha, "Digite a senha do usuario: ");

    // Lê a senha de administrador
    MascararSenha(senhaAdmin, "Digite a senha de administrador caso voce seja admin ou digite 0 para ignorar: ");

    if (strcmp(senhaAdmin, SENHA_ADMIN) == 0) {
        usuario.isAdmin = 1;  // Define como admin
        printf("Usuario cadastrado como administrador!\n");
    } else {
        usuario.isAdmin = 0;  // Define como comum
        printf("Usuario cadastrado como comum.\n");
    }

    // Grava os dados no arquivo
    arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravação!\n");
        return;
    }

    fprintf(arquivo, "%s %s %s %d\n", usuario.nome, usuario.email, usuario.senha, usuario.isAdmin);
    fclose(arquivo);  // Não esqueça de fechar o arquivo

    printf("Usuario cadastrado com sucesso!\n");
}

int LoginUsuario() {

    char email[50], senha[50], emailLido[50], senhaLida[50], nomeLido[50];
    int tipoUsuario;
    FILE *arquivo = fopen("usuarios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de usuários!\n");
        return -1;
    }

    printf("Digite seu email: ");
    scanf("%s", email);
    
    MascararSenha(senha, "Digite sua senha: ");

    while (fscanf(arquivo, "%s %s %s %d", nomeLido, emailLido, senhaLida, &tipoUsuario) != EOF) {
        if (strcmp(email, emailLido) == 0 && strcmp(senha, senhaLida) == 0) {
            printf("Bem-vindo, %s!\n", nomeLido);  // Exibe o nome do usuário
            fclose(arquivo);
            return tipoUsuario;
        }
    }

    fclose(arquivo);
    printf("Email ou senha incorretos!\n");
    return -1;
}

void EditarFuncionario() {
    Usuario usuario;
    FILE *arquivo;
    char emailExistente[50], senhaExistente[50], nomeExistente[50];
    int isAdminExistente;
    char emailParaExcluir[50];
    int encontrado = 0;

    // Abre o arquivo para leitura
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Lê os dados do arquivo
    printf("Lista de e-mails dos funcionários:\n");
    while (fscanf(arquivo, "%s %s %s %d", nomeExistente, emailExistente, senhaExistente, &isAdminExistente) != EOF) {
        printf("%s\n", emailExistente);
    }
    fclose(arquivo);

    // Pergunta se deseja excluir algum funcionário
    printf("Digite o e-mail do funcionário que deseja excluir ou pressione Enter para cancelar: ");
    scanf("%s", emailParaExcluir);

    if (strlen(emailParaExcluir) == 0) {
        printf("Operação cancelada.\n");
        return;
    }

    // Abre o arquivo para leitura e um arquivo temporário para escrita
    arquivo = fopen("usuarios.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Copia os dados, exceto o funcionário a ser excluído, para o arquivo temporário
    while (fscanf(arquivo, "%s %s %s %d", nomeExistente, emailExistente, senhaExistente, &isAdminExistente) != EOF) {
        if (strcmp(emailExistente, emailParaExcluir) != 0) {
            fprintf(temp, "%s %s %s %d\n", nomeExistente, emailExistente, senhaExistente, isAdminExistente);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    // Substitui o arquivo original pelo arquivo temporário
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");

    if (encontrado) {
        printf("Funcionario excluído com sucesso!\n");
    } else {
        printf("Funcionario não encontrado!\n");
    }
}
