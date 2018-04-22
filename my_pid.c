/*
Implementation of the linux pid command in C
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if(argc != 1)
	{
		printf("There is no need for command line arguments!\n");
	}
	
	int pid = getpid();
	int ppid = getppid();
	
	if (pid > 0)
	{
	 	printf("Your process is %d\n", pid);
	}
	else
	{
		printf("There is an eror with your process id %d\n", ppid);
	}
	
	if (ppid > 0)
	{
		printf("You have been called from a process with id %d\n", ppid);
	}
	else
	{
		printf("There was an error while getting the parent process id: \
							%d!", ppid);
	}
	
	return 0;
}
