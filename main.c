#include "shell.h"
/**
 * main - the main entry point
 * @ac: the arguement counter
 * @av: the arguement vector
 * Return: 0 Always success
 */
int main(int ac, char **av)
{
	cmd_t cmd[] = {CMD_INIT};
	int file = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file)
			: "r" (file));
	if (ac == 2)
	{
		file = open(av[1], O_RDONLY);
		if (file == -1)
		{
			 if (errno == EACCES)
				 exit(126);
			 if (errno = ENOENT)
			 {

				 _eputs(av[0]);
				 _eputs("Can't open file");
				 _eputs(av[1]);
				 _eputchar('\n');
				 _eputchar(FLUSH_BUF);
				 exit(127);
			 }
			 return (EXIT_FAILURE);
		}
		cmd->readfd = file;
	}
	populate_env_list(cmd);
	read_history(cmd);
	hsh(cmd, av);
	return (EXIT_SUCCESS);
}
