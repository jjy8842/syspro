#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;
    char buffer[BUFFER_SIZE];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        close(pipe_fd[0]);
        printf("parent process start\n");
        printf("input string: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        write(pipe_fd[1], buffer, strlen(buffer) + 1);
        close(pipe_fd[1]);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, BUFFER_SIZE);
        to_uppercase(buffer);
        printf("%s\n", buffer);
        close(pipe_fd[0]);
        exit(0);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
