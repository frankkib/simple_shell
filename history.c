#include "shell.h"
/**
 * get_history_file - gets the history file
 * @cmd: parameter struct
 * Return: allocated string containg history file
 */
char *get_history_file(cmd_t *cmd)
{
	char *buf, *dir;

	dir = _getenv(cmd, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * read_history - reads history from file
 * @cmd: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(cmd_t *cmd)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(cmd);


	if (!filename)
		return (0);


	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)

		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(cmd, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(cmd, buf + last, linecount++);
	free(buf);
	cmd->histcount = linecount;
	while (cmd->histcount-- >= HIST_MAX)
		delete_node_at_index(&(cmd->history), 0);
	renumber_history(cmd);
	return (cmd->histcount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @cmd: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int build_history_list(cmd_t *cmd, char *buf, int linecount)
{
	list_t *node = NULL;

	if (cmd->history)
		node = cmd->history;
	add_node_end(&node, buf, linecount);

	if (!cmd->history)
		cmd->history = node;
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @cmd: Structure containing potential arguments. Used to maintain
 * Return: the new histcount
 */
int renumber_history(cmd_t *cmd)
{
	list_t *node = cmd->history;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->next;
	}
	return (cmd->histcount = i);
}
