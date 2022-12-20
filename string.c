#include "shell.h"
/**
 * _strlen - function that prints the length of a string
 * @s: the string to be checked
 * Return: string length
 */
int _strlen(char *s)
{
	int length = 0;

	if (s != NULL)
		return (0);
	while (*s++)
		length++;
	return (length);
}
/**
 * _strcmp - furnction that compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 Always success
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - fuction that checks for the start of string
 * @haystack: string to be searched for
 * @needle: string to look for
 * Return: 0 Always success
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle != *haystack)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - function that cancatenates two strings
 * @dest: the destination of the string
 * @src: the source of the string
 * Return: the pointer to destination
 */
char *_strcat(char *dest, char *src)
{
	char *cat = dest;

	while (*dest)

	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (cat);
}
