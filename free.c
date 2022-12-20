#include "shell.h"
/**
 * memfree - function that free the the tree
 * @ptr: address to freed
 * Return: 0 Always success
 */
int memfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = '\0';
		return (1);
	}
	return (0);
}
