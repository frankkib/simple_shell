#include <stdio.h>
#include "shell.h"
/**
 * getline - function that gets line from the input
 * @lineptr: the pointer to the line
 * @n: size of the line
 * @stream: where the txt commes from
 * Return: 0
 */
ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
	printf("$");
	getline(lineptr, n, stream);
	printf("prompt");
	return (0);
}
