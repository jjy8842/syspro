#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	char c;

	if (argc >= 3 && strcmp(argv[1], "0") == 0)
	{
		fp1 = fopen(argv[2], "r");
		if (fp1 == NULL) 
		{
			fprintf(stderr, "File %s Open Error\n", argv[2]);
			return 2;
		}
		
		fp2 = fopen(argv[3], "w");
		
		while ((c = fgetc(fp1)) != EOF)
			fputc(c, fp2);
		
		fclose(fp1);
		fclose(fp2);
		return 0;
	}
	else if (argc >= 3 && strcmp(argv[1], "1") == 0)
	{
		fp1 = fopen(argv[2], "r");
		if (fp1 == NULL) {
			fprintf(stderr, "File %s Open Error\n", argv[1]);
			return 2;
		}
		
		fp2 = fopen(argv[3], "w");
		
		while ((c = fgetc(fp1)) != EOF)
			fputc(tolower(c), fp2);
		
		fclose(fp1);
		fclose(fp2);
		return 0;	
	}
	else if (argc >= 3 && strcmp(argv[1], "2") == 0)
	{
		fp1 = fopen(argv[2], "r");
		if (fp1 == NULL) {
			fprintf(stderr, "File %s Open Error\n", argv[1]);
			return 2;
		}
		
		fp2 = fopen(argv[3], "w");
		
		while ((c = fgetc(fp1)) != EOF)
			fputc(toupper(c), fp2);
		
		fclose(fp1);
		fclose(fp2);
		return 0;
	}    
	else
	{
		perror("-1");
 		return 1;
	}
}
