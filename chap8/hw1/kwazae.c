#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[])
{
	if (argc >= 2 && strcmp(argv[1], "-e") == 0)
	{
		if (argc >= 3 && strcmp(argv[2], "HOME") == 0 )
		{
			char *ptr;

			ptr = getenv("HOME");
			printf("HOME = %s \n", ptr);
			exit(0);
		}
		else if (argc >= 3 && strcmp(argv[2], "SHELL") == 0 )
		{
			char *ptr;

			ptr = getenv("SHELL");
			printf("SHELL = %s \n", ptr);
			exit(0);
		}
		else if (argc >= 3 && strcmp(argv[2], "PATH") == 0 )
		{
			char *ptr;

			ptr = getenv("PATH");
			printf("PATH = %s \n", ptr);
			exit(0);
 		}
		else
		{
			char **ptr;
			extern char **environ;

			for (ptr = environ; *ptr != 0; ptr++)
				printf("%s \n", *ptr);
		
			exit(0);
		}
	}
	else if (argc >= 2 && strcmp(argv[1], "-u") == 0)
	{
		printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
		printf("My Valid User ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
	}

	else if (argc >= 2 && strcmp(argv[1], "-g") == 0)
	{
		printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
		printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
	}
	else if (argc >= 2 && strcmp(argv[1], "-i") == 0)
	{
		printf("my process number : [%d] \n", getpid());
	}
	else if (argc >= 2 && strcmp(argv[1], "-p") == 0)
	{
		printf("my parent's process number : [%d] \n", getppid());
	}
	else
	{
		perror("-1");
 		return 1;
	}
}
