#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SENHA_ADMIN "admin123"


typedef struct {
    char email[50];
    char senha[50];
    int isAdmin;
} Usuario;

void CadastrarUsuario()
{
    
    char senhaAdmin[50];
    Usuario usuario;
    FILE *arquivo;
    char emailExistente[50], senhaExistente[50];
    int isAdminExistente;
    int emailJaExiste = 0;

    
    printf("Digite o email do usuario: ");
    scanf("%s", usuario.email);

    arquivo = fopen("usuarios.txt", "r");
        if (arquivo != NULL) {
        while (fscanf(arquivo, "%s %s %d", emailExistente, senhaExistente, &isAdminExistente) != EOF) {
            if (strcmp(emailExistente, usuario.email) == 0) {
                printf("Erro: Email ja cadastrado!\n");
                emailJaExiste = 1;
                break;
            }
        }
        fclose(arquivo);
    }
    if (emailJaExiste) {
        return; 
    }
    printf("Digite a senha do usuario: ");
    scanf("%s", usuario.senha);
    printf("Digite a senha de administrador caso voce seja admin ou digite 0 para ignorar: ");
    scanf("%s", senhaAdmin);


    if (strcmp(senhaAdmin, SENHA_ADMIN) == 0) {
        usuario.isAdmin = 1; 
        printf("Usuario cadastrado como administrador!\n");
    } else {
        usuario.isAdmin = 0; 
        printf("Usuario cadastrado como comum.\n");
    }

    
    arquivo = fopen("usuarios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    
    fprintf(arquivo, "%s %s %d\n", usuario.email, usuario.senha, usuario.isAdmin);
    fclose(arquivo);

    printf("Usuario cadastrado com sucesso!\n");
}

void LoginUsuario()
{
    Usuario usuario;
    FILE *arquivo;
    char emailExistente[50], senhaExistente[50];
    int verificaAdmin = 0;

    printf("Digite seu email: ");
    scanf("%s", usuario.email);
    printf("Digite sua senha: ");
    scanf("%s", usuario.senha);

    arquivo = fopen("usuarios.txt", "r");
    if (arquivo != NULL) {
        while (fscanf(arquivo, "%s %s %d", emailExistente, senhaExistente, &verificaAdmin) != EOF) {
            if (strcmp(emailExistente, usuario.email) == 0 && strcmp(senhaExistente, usuario.senha) == 0) {
                printf("Logado com Sucesso!\n");
                fclose(arquivo);
                return; 
            }
        }
        printf("Email ou senha incorretos.\n");
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de usuarios.\n");
    }
}