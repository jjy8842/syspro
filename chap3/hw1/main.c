#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char str[5][MAXLINE];
char swap[MAXLINE];

int main(void)
{
        for(int i=0; i<5; i++)
        {
         	fgets(line, MAXLINE, stdin);
         	line[strcspn(line, "\n")] = '\0';
		copy(line, str[i]);
        }

        for(int i=0; i<5; i++)
        {
                for(int j=i+1; j<5; j++)
                {
                	if(strlen(str[i]) < strlen(str[j]))
                        {
                                copy(str[i], swap);
                                copy(str[j], str[i]);
                                copy(swap, str[j]);
                        }
                }
        }
        
	for(int i=0; i<5; i++)
        {
                printf("%s\n", str[i]);
        }

        return 0;
}
