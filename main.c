#include "UsuarioService.c"

int main() {
    int opcao;

    while (1) // Loop infinito até que o usuário decida parar
    {
        // Exibe o menu e pede a entrada do usuário
        printf("\n1. Cadastrar Usuario\n");
        printf("2. Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário

        switch (opcao)
        {
            case 1:
                CadastrarUsuario(); // Chama a função de cadastro
                break;
            case 2:
                return 0;    
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}