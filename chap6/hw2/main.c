#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <stdbool.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, bool, bool);

int main(int argc, char **argv)
{
	DIR *dp;
	char *dir;
	struct stat st;
	struct dirent *d;
	char path[BUFSIZ+1];
	
	bool opt_l = false;  
    	bool opt_a = false;  
    	bool opt_h = false;

	dir = ".";

	for (int i = 1; i < argc; i++) 
	{
        	if (argv[i][0] == '-') 
		{
            		for (int j = 1; j < strlen(argv[i]); j++) 
			{
                		if (argv[i][j] == 'l') opt_l = true;
                		else if (argv[i][j] == 'a') opt_a = true;
                		else if (argv[i][j] == 'h') opt_h = true;
            		}
        	} 
		else 
		{
            		dir = argv[i];
        	}
    	}	

    	if ((dp = opendir(dir)) == NULL) 
	{
        	perror(dir);
        	exit(1);
    	}	
	
	while ((d = readdir(dp)) != NULL) 
	{
        	if (!opt_a && d->d_name[0] == '.') continue;

        	sprintf(path, "%s/%s", dir, d->d_name);
        	if (lstat(path, &st) < 0)
            		perror(path);
        	else
            		printStat(path, d->d_name, &st, opt_l, opt_h);
    	}	
    	closedir(dp);
    	exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, bool opt_l, bool opt_h)
{
	if (opt_l) 
	{
        	printf("%5d ", st->st_blocks);
        	printf("%c%s ", type(st->st_mode), perm(st->st_mode));

        	printf("%3d ", st->st_nlink);
        	printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);

        	if (opt_h) 
		{
            		char size_str[10];
            		humanReadableSize(size_str, st->st_size);
            		printf("%9s ", size_str);
        	} 
		else 
		{
            		printf("%9d ", (int)st->st_size);
        	}

        	printf("%.12s ", ctime(&st->st_mtime)+4);
    	}
	printf("%s\n", file);
}

char type(mode_t mode)
{
	if (S_ISREG(mode))
		return('-');
	if (S_ISDIR(mode))
		return('d');
	if (S_ISCHR(mode))
		return('c');
	if (S_ISBLK(mode))
		return('b');
	if (S_ISLNK(mode))
		return('l');
	if (S_ISFIFO(mode))
		return('p');
	if (S_ISSOCK(mode))
		return('s');
	return('?');
}

char* perm(mode_t mode)
{
	static char perms[10];
    	strcpy(perms, "---------");

    	for (int i=0; i < 3; i++) 
	{
        	if (mode & (S_IRUSR >> i*3))
            		perms[i*3] = 'r';
        	if (mode & (S_IWUSR >> i*3))
            		perms[i*3+1] = 'w';
        	if (mode & (S_IXUSR >> i*3))
            		perms[i*3+2] = 'x';
    	}
    	return(perms);
}

void humanReadableSize(char *buf, long size)
{
	if (size >= (1 << 30))
        	sprintf(buf, "%.1fG", size / (float)(1 << 30));
    	else if (size >= (1 << 20))
        	sprintf(buf, "%.1fM", size / (float)(1 << 20));
    	else if (size >= (1 << 10))
        	sprintf(buf, "%.1fK", size / (float)(1 << 10));
    	else
        	sprintf(buf, "%ldB", size);
}
