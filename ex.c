#include "shell.h"

/**
 * _scramble_copy - duplicates a string
 * @result: the destination string to copy to
 * @source: the source string to copy from
 * @max_len: the maximum characters to copy
 * Return: the duplicated string
 */
char *_scramble_copy(char *result, char *source, int max_len)
{
	int index, pos;
	char *r = result;

	index = 0;
	while (source[index] != '\0' && index < max_len - 1)
	{
		result[index] = source[index];
		index++;
	}
	if (index < max_len)
	{
		pos = index;
		while (pos < max_len)
		{
			result[pos] = '\0';
			pos++;
		}
	}
	return (r);
}

/**
 * _scramble_concat - combines two strings
 * @result: the first string
 * @source: the second string
 * @max_len: the maximum bytes to use
 * Return: the combined string
 */
char *_scramble_concat(char *result, char *source, int max_len)
{
	int index, pos;
	char *r = result;

	index = 0;
	pos = 0;
	while (result[index] != '\0')
		index++;
	while (source[pos] != '\0' && pos < max_len)
	{
		result[index] = source[pos];
		index++;
		pos++;
	}
	if (pos < max_len)
		result[index] = '\0';
	return (r);
}

/**
 * _scramble_seek - searches for a character in a string
 * @str: the string to search within
 * @ch: the character to look for
 * Return: a pointer to the found character or NULL
 */
char *_scramble_seek(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
}
