#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line.
 * @cmd: Structure containing potential arguments
 * Return: Always 0
 */
int _myhistory(cmd_t *cmd)
{
	print_list(cmd->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @cmd: parameter struct
 * @str: string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(cmd_t *cmd, char *str)
{
	int ret;
	char *p, c;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(cmd->alias),
		get_node_index(cmd->alias, node_starts_with(cmd->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @cmd: parameter struct
 * @str: string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(cmd_t *cmd, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(cmd, str));

	unset_alias(cmd, str);
	return (add_node_end(&(cmd->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		{
			_putchar(*a);
			_putchar('\'');
			_puts(p + 1);
			_puts("'\n");
			return (0);
		}
	}
	return (1);
}

/**
 * _myalias - mimics alias builtin
 * @cmd: Structure containing potential arguments
 * Return: Always 0
 */
int _myalias(cmd_t *cmd)
{
	int i = 0;
	list_t *node = NULL;
	char *p = NULL;

	if (cmd->argc == 1)
	{
		node = cmd->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; cmd->argv[i]; i++)
	{
		p = _strchr(cmd->argv[i], '=');
		if (p)
			set_alias(cmd, cmd->argv[i]);
		else
			print_alias(node_starts_with(cmd->alias, cmd->argv[i], '='));
	}

	return (0);
}
