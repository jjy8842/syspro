#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
    char str[1024];
    char *command1, *command2;
    char *args1[10], *args2[10];
    int fd[2];
    pid_t pid1, pid2;

    // Check if arguments are provided
    if (argc == 1) {
        printf("[shell] ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0'; // Remove newline character
    } else {
        // Combine all arguments into a single string
        snprintf(str, sizeof(str), "%s", argv[1]);
        for (int i = 2; i < argc; i++) {
            strcat(str, " ");
            strcat(str, argv[i]);
        }
    }

    // Parse the input string to split by "|"
    if (strchr(str, '|') != NULL) {
        command1 = strtok(str, "|");
        command2 = strtok(NULL, "|");

        // Parse command1
        int i = 0;
        args1[i] = strtok(command1, " ");
        while (args1[i] != NULL) {
            i++;
            args1[i] = strtok(NULL, " ");
        }

        // Parse command2
        i = 0;
        args2[i] = strtok(command2, " ");
        while (args2[i] != NULL) {
            i++;
            args2[i] = strtok(NULL, " ");
        }
    } else {
        fprintf(stderr, "Invalid input. Use the format: command1 | command2\n");
        exit(1);
    }

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Create the first child process to execute command1
    if ((pid1 = fork()) == 0) {
        close(fd[READ]); // Close unused read end
        dup2(fd[WRITE], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(fd[WRITE]); // Close original write end
        execvp(args1[0], args1);
        perror("execvp");
        exit(1);
    }

    if (pid1 < 0) {
        perror("fork");
        exit(1);
    }

    // Create the second child process to execute command2
    if ((pid2 = fork()) == 0) {
        close(fd[WRITE]); // Close unused write end
        dup2(fd[READ], STDIN_FILENO); // Redirect stdin to pipe read end
        close(fd[READ]); // Close original read end
        execvp(args2[0], args2);
        perror("execvp");
        exit(1);
    }

    if (pid2 < 0) {
        perror("fork");
        exit(1);
    }

    // Parent process: Close both ends of the pipe
    close(fd[READ]);
    close(fd[WRITE]);

    // Wait for both children to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
