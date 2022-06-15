#include <stdio.h>
#include <stdlib.h>

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
			printf("%s", buffer);
		else
			break;
	}
	return (0);
}
