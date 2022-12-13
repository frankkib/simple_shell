#include <stdio.h>
#include <stdlib.h>
/**
 * main - the beginning of the fuction
 * @ac: the agrument counter
 * @av: the argument vector
 * Return: 0
 */
int main(int ac, char **av)
{
	int num = 0;
	char *temp = "hello kenya";

	 printf("%s\n", *av);
	 printf("%d\n", ac);
	if (!temp[num])
	{
		printf("%d\n", temp[num]);
		temp++;
	}
	return (0);
}
