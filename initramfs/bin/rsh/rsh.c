#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD 128
#define MAX_ARGS 16

int main() {
    char cmd[MAX_CMD];

    while (1) {
        printf("rsh:\x1b[34m\x1b[1mrythin\x1b[0m \x1b[1m#\x1b[0m ");
        fflush(stdout);

        if (!fgets(cmd, sizeof(cmd), stdin)) {
            break;
        }

        cmd[strcspn(cmd, "\n")] = 0;

        if (strlen(cmd) == 0) continue;

        char *args[MAX_ARGS];
        int i = 0;
        char *token = strtok(cmd, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("rsh err");
            exit(1);
        } else if (pid > 0) {

            wait(NULL);
        } else {
            perror("fork");
        }
    }

    return 0;
}
