#include "shell.h"
/**
 * main - the main entry point
 * @ac: the arguement counter
 * @av: the arguement vector
 * Return: 0 Always success
 */
int main(int ac, char **av)
{
	cmd_t cmd[] = { CMD_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		cmd->readfd = fd;
	}
	populate_env_list(cmd);
	read_history(cmd);
	hsh(cmd, av);
	return (EXIT_SUCCESS);
}
