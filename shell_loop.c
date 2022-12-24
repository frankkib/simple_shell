#include "shell.h"

/**
 * hsh - main shell loop
 * @cmd: the parameter & return info struct
 * @av: the argument vector from main()
 *Return: 0 on success, 1 on error, or error code
 */
int hsh(cmd_t *cmd, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_cmd(cmd);
		if (interactive(cmd))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(cmd);
		if (r != -1)
		{
			set_cmd(cmd, av);
			builtin_ret = find_builtin(cmd);
			if (builtin_ret == -1)
				find_cmd(cmd);
		}
		else if (interactive(cmd))
			_putchar('\n');
		free_cmd(cmd, 0);
	}
	write_history(cmd);
	free_cmd(cmd, 1);
	if (!interactive(cmd) && cmd->status)
		exit(cmd->status);
	if (builtin_ret == -2)
	{
		if (cmd->err_num == -1)
			exit(cmd->status);
		exit(cmd->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 *0 if builtin executed successfully,
 */
int find_builtin(cmd_t *cmd)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};


	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(cmd->argv[0], builtintbl[i].type) == 0)
		{
			cmd->line_count++;
			built_in_ret = builtintbl[i].func(cmd);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 * Return: void
 */
void find_cmd(cmd_t *cmd)
{
	char *path = NULL;
	int i, k;


	cmd->path = cmd->argv[0];
	if (cmd->linecount_flag == 1)
	{
		cmd->line_count++;
		cmd->linecount_flag = 0;
	}
	for (i = 0, k = 0; cmd->arg[i]; i++)
		if (!is_delim(cmd->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(cmd, _getenv(cmd, "PATH="), cmd->argv[0]);
	if (path)
	{
		cmd->path = path;
		fork_cmd(cmd);
	}
	else
	{
		if ((interactive(cmd) || _getenv(cmd, "PATH=")
			|| cmd->argv[0][0] == '/') && is_cmd(cmd, cmd->argv[0]))
			fork_cmd(cmd);
		else if	(*(cmd->arg) != '\n')
		{
			cmd->status = 127;
			print_error(cmd, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 * Return: void
 */
void fork_cmd(cmd_t *cmd)
{
	pid_t child_pid;


	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(cmd->path, cmd->argv, get_environ(cmd)) == -1)
		{
			free_cmd(cmd, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(cmd->status));
		if (WIFEXITED(cmd->status))
		{
			cmd->status = WEXITSTATUS(cmd->status);
			if (cmd->status == 126)
				print_error(cmd, "Permission denied\n");
		}
	}
}
