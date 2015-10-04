/*
Implementation of the linux command wc
*/

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc!= 2)
	{
		printf("Please provide the correct number of arguments\n");
		return -1;
	}	
	
	int inword =0;
	int numberOfWords = 0;
	// get the fileame of the text file
	char *file = argv[1];
	// a character variable
	char ch = ' ';
	//open the text file for reading
	FILE *fp = fopen(file, "r");
	
	if (fp == NULL)
	{
		printf("Error reading %s\n", file);
		return 1;
	}
	
	// start counting words
	while( (ch = fgetc(fp)) != EOF )
	{
		if (ch == ' '|| ch == '\n' || ch == '\t')
		{
			inword = 0;
		}
		else if (inword == 0)
		{
			inword = 1;
			numberOfWords++;
		}
	}
	//close the file
	fclose(fp);
	printf("Number of words found %d\n", numberOfWords);
	
	return 0;
	
}
