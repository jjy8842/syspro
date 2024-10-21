#include <stdio.h>
#include <string.h>
#define MAXLINE 80

int main(int argc, char *argv[])
{
	FILE *fp;
	int c;
	int line = 0;
	char buffer[MAXLINE];

	if (argc < 2)
		fp = stdin;
	
	else if (argc >= 2 && strcmp(argv[1], "-n") == 0)
	{
		fp = fopen(argv[2],"r");
		if (fp == NULL)
		{
			perror("-1");
			return 1;
		}

		while (fgets(buffer, MAXLINE, fp) != NULL)
		{
			line++;
			printf("%3d %s", line, buffer);
		}

		fclose(fp);
		return 0;
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			fp = fopen(argv[i], "r");
			if (fp == NULL)
			{
				perror("-1");
				continue;
			}
			
			c = getc(fp);

			while (c != EOF)
			{
				putc(c, stdout);
				c = getc(fp);
			}
			fclose(fp);
		}
	}
	return 0;
}
