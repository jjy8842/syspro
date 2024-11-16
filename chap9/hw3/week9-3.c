#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void execute_command(char *cmd);

int main() {
    char input[MAX_INPUT];

    printf("Custom Shell Interpreter\n");

    while (1) {
        printf("[shell] ");
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

        execute_command(input);
    }

    return 0;
}

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    int background = 0;
    pid_t pid;

    char *token = strtok(cmd, ";");
    while (token) {
        char *current_cmd = strdup(token);

        if (strchr(current_cmd, '&')) {
            *strchr(current_cmd, '&') = '\0';
            background = 1;
        }

        char *outfile = strchr(current_cmd, '>');
        char *infile = strchr(current_cmd, '<');
        int fd_out = -1, fd_in = -1;

        if (outfile) {
            *outfile = '\0';
            outfile++;
            while (*outfile == ' ') outfile++;
            fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("Output redirection failed");
                free(current_cmd);
                return;
            }
        }

        if (infile) {
            *infile = '\0';
            infile++;
            while (*infile == ' ') infile++;
            fd_in = open(infile, O_RDONLY);
            if (fd_in < 0) {
                perror("Input redirection failed");
                free(current_cmd);
                return;
            }
        }

        int i = 0;
        char *arg = strtok(current_cmd, " ");
        while (arg && i < MAX_ARGS - 1) {
            args[i++] = arg;
            arg = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid = fork();
        if (pid == 0) {
            if (fd_out != -1) {
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            if (fd_in != -1) {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            execvp(args[0], args);
            perror("Execution failed");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            if (!background) {
                waitpid(pid, NULL, 0); 
            }
        } else {
            perror("Fork failed");
        }

        if (fd_out != -1) close(fd_out);
        if (fd_in != -1) close(fd_in);

        free(current_cmd);
        token = strtok(NULL, ";");
    }
}
