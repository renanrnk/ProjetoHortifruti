#include "UsuarioService.c"
#include "ProdutoService.c"
#include "TelaService.c"

int main() {
    
    int opcao, opcaoLogado, tipoUsuario;

    while (1) {
        TelaLogin();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                CadastrarUsuario();  // Cadastra um novo produto
                break;

            case 2:
                tipoUsuario = LoginUsuario();  // Realiza login e retorna o tipo de usuário

                if (tipoUsuario == 0) {  // Funcionário
                    while (1) {
                        TelaInicial();
                        scanf("%d", &opcaoLogado);
                        switch (opcaoLogado) {
                            case 1:
                                CadastrarProduto();
                                break;
                            case 2:
                                ListarProduto();
                                break;
                            case 3:
                                printf("Acessando a balança...\n");
                                break;
                            case 4:
                                return 0;  // Sai do sistema
                            default:
                                printf("Opcao invalida!\n");
                        }
                    }
                } else if (tipoUsuario == 1) {  // Chefe
                    while (1) {
                        TelaInicialGerente();
                        scanf("%d", &opcaoLogado);
                        switch (opcaoLogado) {
                            case 1:
                                CadastrarProduto();
                                break;
                            case 2:
                                ListarProduto();
                                break;
                            case 3:
                                printf("Acessando a balança...\n");
                                break;
                            case 4:
                                printf("Editando funcionários...\n");
                                // Chamar função de edição de funcionários aqui
                                break;
                            case 5:
                                EditarProduto();
                                break;
                            case 6:
                                return 0;  // Sai do sistema
                            default:
                                printf("Opcao invalida!\n");
                        }
                    }
                } else {
                    printf("Login falhou!\n");
                }
                break;

            case 3:
                return 0;  // Sai do programa principal

            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}