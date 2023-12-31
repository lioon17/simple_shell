#include "shell.h"

/**
 * bfree- Releases memory occupied by a pointer
 * @ptr: The address of the pointer to be freed.
 *
 * Return: 1 if memory was released, else 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
