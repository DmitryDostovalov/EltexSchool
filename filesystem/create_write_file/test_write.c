#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

#define FILENAME "my_file.txt"
#define BUF_SIZE 80

int main()
{
	int fd = -1;
	fd = open(FILENAME,
		  O_CREAT | O_RDWR,
		  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if(-1 == fd)
	{
		perror("Cannot open a file!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("File created.\n");
	}


	char buf[BUF_SIZE] = "Hello world!";
	size_t count = strlen(buf);
	if(count > BUF_SIZE)
	{
		printf("Too long text!\n");
		close(fd);
		exit(EXIT_FAILURE);
	}

	size_t write_bytes_cnt = 0;
	write_bytes_cnt = write(fd, buf, count);

	if(write_bytes_cnt != count)
	{
		perror("Write error!\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Text added.\n");
	}

	if(close(fd) != 0)
	{
		perror("Error closing file!\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
