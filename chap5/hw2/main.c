#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) 
{
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) 
    {
        perror("-1");
        return 1;
    }

    char **lines = NULL;
    size_t line_count = 0;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, sizeof(buffer), file)) {
        lines = realloc(lines, sizeof(char *) * (line_count + 1));
        if (lines == NULL) 
	{
            perror("-1");
            fclose(file);
            return 1;
        }

        lines[line_count] = malloc(strlen(buffer) + 1);
        if (lines[line_count] == NULL) 
	{
            perror("-1");
            fclose(file);
            return 1;
        }

        strcpy(lines[line_count], buffer);
        line_count++;
    }

    fclose(file);

    for (long i = line_count - 1; i >= 0; i--) 
    {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    free(lines);

    return 0;
}

