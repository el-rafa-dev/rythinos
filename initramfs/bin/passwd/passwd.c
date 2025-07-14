#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

#define PASSWORD_FILE "/etc/shadow" // arquivo simulado

void usage(const char *prog) {
    fprintf(stderr, "Uso: %s [usuário]\n", prog);
    exit(1);
}

int main(int argc, char *argv[]) {
    const char *user = NULL;
    char oldpass[128], newpass[128];

    if (argc > 2)
        usage(argv[0]);

    if (argc == 2) {
        user = argv[1];
    } else {
        user = getlogin();
        if (!user) {
            fprintf(stderr, "Não foi possível identificar o usuário.\n");
            return 1;
        }
    }

    printf("Alterando a senha de %s\n", user);

    printf("Senha antiga: ");
    fflush(stdout);
    if (!fgets(oldpass, sizeof(oldpass), stdin)) return 1;
    oldpass[strcspn(oldpass, "\n")] = 0;

    printf("Nova senha: ");
    fflush(stdout);
    if (!fgets(newpass, sizeof(newpass), stdin)) return 1;
    newpass[strcspn(newpass, "\n")] = 0;

    // Aqui você poderia aplicar um hash com crypt() se quiser:
    const char *salt = "$6$RYTHIN$"; // SHA-512 salt estático de exemplo
    char *hashed = crypt(newpass, salt);

    if (!hashed) {
        fprintf(stderr, "Erro ao gerar hash.\n");
        return 1;
    }

    // Simula escrita em um arquivo de senhas (em vez de /etc/shadow)
    FILE *f = fopen(PASSWORD_FILE, "a");
    if (!f) {
        perror("Erro ao abrir arquivo de senhas");
        return 1;
    }

    fprintf(f, "%s:%s\n", user, hashed);
    fclose(f);

    printf("Senha de %s atualizada com sucesso!\n", user);
    return 0;
}
