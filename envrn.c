#include "shell.h"

/**
 * _myenv - prints current environment
 * @cmd: Structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(cmd_t *cmd)
{
	print_list_str(cmd->env);
	return (0);
}

/**
 *  _getenv - gets the value of an environ variable
 * @cmd: Structure containing potential arguments. Used to maintain
 * @name: env var name
 * Return: the value
 */
char *_getenv(cmd_t *cmd, const char *name)
{
	list_t *node = cmd->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *or an existing one
 *@cmd: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: Always 0
 */
int _mysetenv(cmd_t *cmd)
{
	if (cmd->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(cmd, cmd->argv[1], cmd->argv[2]))
	{
		return (0);
		return (1);
	}
	return (0);
}

/**
 * _myunsetenv - Remove an environment variable
 * @cmd: Structure containing potential arguments
 * Return: Always 0
 */
int _myunsetenv(cmd_t *cmd)
{
	int i;

	if (cmd->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= cmd->argc; i++)
	_unsetenv(cmd, cmd->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @cmd: Structure containing potential arguments
 * Return: Always 0
 */
int populate_env_list(cmd_t *cmd)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	add_node_end(&node, environ[i], 0);
	cmd->env = node;
	return (0);
}
