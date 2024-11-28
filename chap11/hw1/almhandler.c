#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void (*custom_signal(int signo, void (*handler)(int)))(int)
{
    struct sigaction act, old_act;

    act.sa_handler = handler;        
    sigemptyset(&act.sa_mask);       
    act.sa_flags = 0;       

    if (sigaction(signo, &act, &old_act) < 0)
    {
        perror("sigaction error");
        return SIG_ERR;
    }

    return old_act.sa_handler;
}

void alarmHandler(int signo)
{
    printf("Wake up\n");
    exit(0);
}

int main()
{
    custom_signal(SIGALRM, alarmHandler);
    alarm(5);                            

    short i = 0;
    while (1)
    {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }

    return 0;
}

