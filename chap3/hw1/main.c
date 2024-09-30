#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char swap[MAXLINE];
char str[5][MAXLINE];

int main()
{
        for(int i=0; i<5; i++)
        {
                if (fgets(line, MAXLINE, stdin) != NULL)
                {
                        copy(str[i], line);
                }
        }

        for(int i=0; i<5; i++)
        {
                for(int j=i+1; j<5; j++)
                {
                        if(strlen(str[i]) < strlen(str[j]))
                        {
                                copy(swap, str[i]);
                                copy(str[i], str[j]);
                                copy(str[j], swap);
                        }
                }
        }
        for(int i=0; i<5; i++)
        {
                printf("%s", str[i]);
        }
        return 0;
}
