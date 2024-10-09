#include "UsuarioService.c"


int main() {
    int opcao;

    while (1) 
    {
        
        printf("\n1. Cadastrar Usuario\n");
        printf("2. Fazer Login\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao); 

        switch (opcao)
        {
            case 1:
                CadastrarUsuario(); 
                break;
            case 2:
                LoginUsuario(); 
                break;
            case 3:
                return 0;
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}


