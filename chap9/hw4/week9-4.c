#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void execute_command(char *input) {
    char *args[MAX_ARGS];
    char *token;
    char *saveptr;
    int background = 0;

    int i = 0;
    token = strtok_r(input, " ", &saveptr);
    while (token != NULL && i < MAX_ARGS - 1) {
        if (strcmp(token, "&") == 0) {
            background = 1;
            break;
        }
        args[i++] = token;
        token = strtok_r(NULL, " ", &saveptr);
    }
    args[i] = NULL;

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) {
        execvp(args[0], args);
        perror("Execution failed");
        exit(EXIT_FAILURE);
    } else {
        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("Process running in background: PID %d\n", pid);
        }
    }
}

int main() {
    char input[MAX_INPUT];

    printf("Custom Shell Interpreter\n");

    while (1) {
        printf("pls input cmd : ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            printf("\nExiting shell...\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        if (strlen(input) > 0) {
            execute_command(input);
        }
    }

    return 0;
}

