#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(int argc, char *argv[])
{
	int fd, id;
	char c;
	struct student record;
	
	printf("--bookquery--");
	scanf("0: list of all books, 1: list of available books %c", &c);

	if (c == 0)
	{
		fd = open(argv[1], O_RDONLY);
		printf("id   bookname    author   year  numofborrow borrow");
		lseek(fd, (id)*sizeof(record), SEEK_SET);
		for (int i = 0; i < 4 ;i++)
		{
			lseek(fd, (i)*sizeof(record), SEEK_SET);
			if ((read(fd, (char *) &record, sizeof(record)) > 0))
			{
				printf("%-1d %-9s %-8d %-4d %-1d %-5d\n",record.id, record.bookname, record.author, record.year, record.numofborrow, record.borrow);
			}
		close(fd);
		exit(0);
		}
	}
	else if (c == 1)
	{
		fd = open(argv[1], O_RDONLY);
		printf("");

		close(fd);
		exit(0);
	}

}
