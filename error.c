#include "shell.h"

/**
 *_eputs - prints input string
 * @str:  string to be printed
 * Return: void
 */
void _eputs(char *str)
{
	int i = 0;

	if (str == 0)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes character c to stderr
 * @c: character to print
 * Return: On success 1.
 * On error, -1 is returned
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (i >= WRITE_BUF_SIZE ||  c == FLUSH_BUF)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUF)
	{
		buf[i++] = c;
		return (1);
	}
	return (0);
}

/**
 * _putfd - writes the character c to given fd
 * @c: character to print
 * @fd: filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == FLUSH_BUF || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUF)
	buf[i++] = c;
		return (1);
}

/**
 * _putsfd - prints an input string
 * @str: string to be printed
 * @fd: filedescriptor to write to
 * Return: number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
