#include "shell.h"

/**
 * chain_input - buffers chained commands
 * @custom_info: parameter structure
 * @custom_buf: address of buffer
 * @custom_len: address of len variable
 *
 * Returns: bytes read
 */
ssize_t chain_input(info_t *custom_info, char **custom_buf, size_t *custom_len)
{
	ssize_t read_bytes = 0;
	size_t len_pending = 0;

	if (!*custom_len)
	{
		free(*custom_buf);
		*custom_buf = NULL;
		signal(SIGINT, sigintHandler);
		read_bytes = buffered_input(custom_info, custom_buf, &len_pending);
		if (read_bytes > 0)
		{
			if ((*custom_buf)[read_bytes - 1] == '\n')
			{
				(*custom_buf)[read_bytes - 1] = '\0';
				read_bytes--;
			}
			custom_info->linecount_flag = 1;
			remove_comments(*custom_buf);
			build_history_list(custom_info, *custom_buf, custom_info->histcount++);
		}
	}
	return (read_bytes);
}

/**
 * get_input - gets a line without newline
 * @custom_info: parameter structure
 *
 * Returns: bytes read
 */
ssize_t get_input(info_t *custom_info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t read_bytes = 0;
	char **buf_p = &(custom_info->arg), *p;

	_putchar(BUF_FLUSH);
	read_bytes = chain_input(custom_info, &buf, &len);
	if (read_bytes == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(custom_info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(custom_info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			custom_info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (read_bytes);
}

/**
 * read_buffered - reads a buffer
 * @custom_info: parameter structure
 * @buf: buffer
 * @i: size
 *
 * Returns:the  read status
 */
ssize_t read_buffered(info_t *custom_info, char *buf, size_t *i)
{
	ssize_t read_status = 0;

	if (*i)
		return (0);
	read_status = read(custom_info->readfd, buf, READ_BUF_SIZE);
	if (read_status >= 0)
		*i = read_status;
	return (read_status);
}

/**
 * custom_getline - gets next input line from STDIN
 * @custom_info: parameter structure
 * @ptr: address of buffer pointer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Returns: the number of read bytes
 */
int custom_getline(info_t *custom_info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_status = 0, read_bytes = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		read_bytes = *length;
	if (i == len)
		i = len = 0;

	read_status = read_buffered(custom_info, buf, &len);
	if (read_status == -1 || (read_status == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, read_bytes, read_bytes ? read_bytes + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (read_bytes)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	read_bytes += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = read_bytes;
	*ptr = p;
	return (read_bytes);
}

/**
 * sigintHandler - blocks Ctrl-C
 * @sig_num: signal number
 *
 * Returns: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
