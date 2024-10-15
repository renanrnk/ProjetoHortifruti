#include "UsuarioService.c"
#include "ProdutoService.c"
#include "TelaService.c"

int main() {
    int opcao;
    int opcaoLogado;

    while (1) {
        TelaLogin();       
        scanf("%d", &opcao); 

        switch (opcao) {
            case 1:
                CadastrarProduto(); 
                break;
            case 2:
                if (LoginUsuario() == 1) {
                    while (1) { // Permanece no menu de produtos até sair
                        TelaInicial();
                        scanf("%d", &opcaoLogado);
                        switch (opcaoLogado) {
                            case 1:
                                CadastrarProduto();
                                break;
                            case 2:
                                ListarProduto();  // Lógica para listar produtos
                                break;
                            case 3:
                                return 0; // Sai do programa
                            default:
                                printf("Opcao invalida!\n");
                        }
                    }
                }
                break;
            case 3:
                return 0; // Sai do programa principal
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}


