#include "1.h"
#include "2.h"
#include "3.h"

int main() {
    int opcao, opcaoLogado, tipoUsuario;

    while (1) {
        TelaLogin();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                CadastrarUsuario();
                system("pause");
                system("cls");
                break;

            case 2:
                tipoUsuario = LoginUsuario();

                if (tipoUsuario == 0) {  // Funcionário
                    while (1) {
                        TelaInicial();
                        scanf("%d", &opcaoLogado);
                        switch (opcaoLogado) {
                            case 1:
                                CadastrarProduto();
                                system("pause");
                                system("cls");
                                break;
                            case 2:
                                ListarProduto();
                                system("pause");
                                system("cls");
                                break;
                            case 3:
                                Balanca();
                                system("pause");
                                system("cls");
                                break;
                            case 4:
                                return 0;  // Sai do sistema
                            default:
                                printf("Opcao invalida!\n");
                        }
                    }
                } else if (tipoUsuario == 1) {  // Chefe
                    while (1) {
                        TelaInicialChefe();
                        scanf("%d", &opcaoLogado);
                        switch (opcaoLogado) {
                            case 1:
                                CadastrarProduto();
                                system("pause");
                                system("cls");
                                break;
                            case 2:
                                ListarProduto();
                                system("pause");
                                system("cls");
                                break;
                            case 3:
                                Balanca();
                                system("pause");
                                system("cls");
                                break;
                            case 4:
                                EditarFuncionario();
                                system("pause");
                                system("cls");
                                break;
                            case 5:
                                ListarProduto();
                                EditarProduto();
                                system("pause");
                                system("cls");
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
