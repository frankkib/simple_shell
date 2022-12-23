#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(cmd_t *cmd)
{
	int exitcheck;

	if (cmd->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(cmd->argv[1]);
		if (exitcheck == -1)
		{
			cmd->status = 2;
			print_error(cmd, "Illegal number: ");
			_eputs(cmd->argv[1]);
			_eputchar('\n');
			return (1);
		}
		cmd->err_num = _erratoi(cmd->argv[1]);
		return (-2);
	}
	cmd->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(cmd_t *cmd)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;


	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!cmd->argv[1])
	{
		dir = _getenv(cmd, "HOME=");
		if (!dir)
			chdir_ret = /* ?? */
				chdir((dir = _getenv(cmd, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(cmd->argv[1], "-") == 0)
	{
		if (!_getenv(cmd, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(cmd, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* ?? */
			chdir((dir = _getenv(cmd, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(cmd->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(cmd, "can't cd to ");
		_eputs(cmd->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(cmd, "OLDPWD", _getenv(cmd, "PWD="));
		_setenv(cmd, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myhelp(cmd_t *cmd)
{
	char **arg_array;

	arg_array = cmd->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
