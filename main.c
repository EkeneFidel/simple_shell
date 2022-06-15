#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * main - Program to print Hello World
 *
 * Return: 0 (Success) || 1 (Error)
 */
int main(void)
{
	char *buffer;
	size_t len = 1024;
	int read;

	buffer = malloc(sizeof(size_t) * len);

	while (1)
	{
		printf("$ ");
		read = getline(&buffer, &len, stdin);
		if (read != EOF)
		{
			printf("%s", buffer);
		}
	}
	return (0);
}
