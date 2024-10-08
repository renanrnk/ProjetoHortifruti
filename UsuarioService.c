#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SENHA_ADMIN "admin123"

// Definição de um usuário
typedef struct {
    char nome[50];
    char senha[50];
    int isAdmin;
} Usuario;

void CadastrarUsuario()
{
    char senhaAdmin[50];
    Usuario usuario;
    FILE *arquivo;

    // Pede o nome e a senha do usuário
    printf("Digite o nome do usuario: ");
    scanf("%s", usuario.nome);
    printf("Digite a senha do usuario: ");
    scanf("%s", usuario.senha);
    printf("Digite a senha de administrador caso voce seja admin ou pressione digite 0 para ignorar: ");
    scanf("%s", senhaAdmin);

    if (strcmp(senhaAdmin, SENHA_ADMIN) == 0) {
        usuario.isAdmin = 1; // Se a senha for correta, torna-se admin
        printf("Usuario cadastrado como administrador!\n");
    } else {
        usuario.isAdmin = 0; // Caso contrário, é um usuário comum
        printf("Usuario cadastrado como comum.\n");
    }

    // Abre o arquivo em modo de anexação para adicionar novos usuários
    arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Escreve os dados do usuário no arquivo, com isAdmin formatado corretamente
    fprintf(arquivo, "%s %s %d\n", usuario.nome, usuario.senha, usuario.isAdmin);
    fclose(arquivo);

    printf("Usuario cadastrado com sucesso!\n");
}
