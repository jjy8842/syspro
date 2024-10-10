#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 100

char savedText[MAX_LINES][MAX_LINE_LENGTH];
int totalLines = 0;

void readFile(const char* filename) 
{
    int fd = open(filename, O_RDONLY);

    char buf;
    int line = 0, pos = 0;

    while (read(fd, &buf, 1) > 0) 
    {
        if (buf == '\n') 
	{
            savedText[line][pos] = '\0';
            line++;
            pos = 0;
        } 
	else 
	{
            savedText[line][pos++] = buf;
        }
    }

    if (pos > 0) 
    { 
        savedText[line][pos] = '\0';
        line++;
    }

    totalLines = line;
    close(fd);
}

void printLines(char* input) 
{
    if (strcmp(input, "*") == 0) 
    {
        for (int i = 0; i < totalLines; i++) 
	{
            printf("%s\n", savedText[i]);
        }
    } 
    else if (strchr(input, '~') != NULL) 
    {
        int start, end;
        sscanf(input, "%d~%d", &start, &end);
        
	for (int i = start - 1; i < end && i < totalLines; i++) 
	{
            printf("%s\n", savedText[i]);
        }
    } 
    else if (strchr(input, ',') != NULL) 
    {
        char* token = strtok(input, ",");
        while (token != NULL) 
	{
            int lineNum = atoi(token);
            if (lineNum > 0 && lineNum <= totalLines) 
	    {
                printf("%s\n", savedText[lineNum - 1]);
            }
            token = strtok(NULL, ",");
        }
    } 
    else 
    { 
        int lineNum = atoi(input);
        if (lineNum > 0 && lineNum <= totalLines) 
	{
            printf("%s\n", savedText[lineNum - 1]);
        } 
       
    }
}

int main(int argc, char* argv[]) 
{
    readFile(argv[1]);

    printf("File read success\n");
    printf("Total Line : %d\n", totalLines);
    printf("You can choose 1 ~ %d Line\n", totalLines);

    char input[100];
    printf("Pls 'Enter' the line to select : ");
    scanf("%s", input);

    printLines(input);

    return 0;
}
