#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define FILENAME "usuarios.txt"
#define FILENAME "usuarios.txt"

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

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