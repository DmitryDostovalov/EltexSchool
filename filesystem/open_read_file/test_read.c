#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

#define FILENAME "my_file.txt"

int main()
{
	int fd = -1;
	fd = open(FILENAME,
		  O_RDONLY);
	if(-1 == fd)
	{
		perror("Cannot open a file!\n");
		exit(EXIT_FAILURE);
	}


	if(-1 == lseek(fd, 0, SEEK_END))
	{
		perror("Seek error!\n");
		close(fd);
		exit(EXIT_FAILURE);
	}


	char buf;
	long pos = -1;
	while(1)
	{
		if(0 == pos) break;

		pos = lseek(fd, -sizeof(buf), SEEK_CUR);
		if(-1 == pos)
		{
			perror("Seek error!\n");
			close(fd);
			exit(EXIT_FAILURE);
		}

		if(0 == read(fd, &buf, sizeof(buf))) break;
		printf("%c", buf);

		pos = lseek(fd, -sizeof(buf), SEEK_CUR);
		if(-1 == pos)
		{
			perror("Seek error!\n");
			close(fd);
			exit(EXIT_FAILURE);
		}
	}
	printf("\n");

	if(close(fd) != 0)
	{
		perror("Error closing file!\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
