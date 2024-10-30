#include "ProdutoService.c"
#include "TelaService.c"
#include "UsuarioService.c"
#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int opcao, opcaoLogado, tipoUsuario;
    
    while (1) {
        TelaLogin();
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer do stdin em caso de entrada inválida
            while (getchar() != '\n');
            printf("Opcao invalida! Por favor, insira um numero.\n");
            continue;
        }
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
                        if (scanf("%d", &opcaoLogado) != 1) {
                            // Limpa o buffer do stdin em caso de entrada inválida
                            while (getchar() != '\n');
                            printf("Opcao invalida! Por favor, insira um numero.\n");
                            continue;
                        }
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
                        if (scanf("%d", &opcaoLogado) != 1) {
                            // Limpa o buffer do stdin em caso de entrada inválida
                            while (getchar() != '\n');
                            printf("Opcao invalida! Por favor, insira um numero.\n");
                            continue;
                        }
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
