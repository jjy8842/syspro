#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() 
{
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    
    if (pipe(pipefd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    pid = fork(); 
    
    if (pid < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    { 
        close(pipefd[0]); 
        char message[100];
        snprintf(message, sizeof(message), "Send: [%d] Hello from PID %d\n", getpid(), getpid());
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]); 
        exit(EXIT_SUCCESS);
    } 
    else 
    { 
        close(pipefd[1]); 
        read(pipefd[0], buffer, sizeof(buffer));
        printf("%s", buffer); 
        snprintf(buffer, sizeof(buffer), "Recv: [%d] Hello from PID %d\n", getpid(), pid);
        printf("%s", buffer); 
        close(pipefd[0]); 
    }
    return 0;
}
