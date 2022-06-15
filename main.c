#include "shell.h"

/**
 * main - execute the interactive or non-interactive mode of the shell.
 * @ac:argumen count (unused).
 * @av:argument vector (unused).
 * @env: environment variable.
 * Return: always 0 (success).
 */
int main(__attribute__((unused)) int ac, char **av, char **env)
{
	list_t *path;
	char *program_name = av[0];
	int aux, mode = 0;

	signal(SIGINT, SIG_IGN);
	path = list_path(env);
	if (isatty(0))
		mode = 1;
	aux = start_shell(path, env, program_name, mode);
	free_list(path);
	return (aux);
}


/**
 * start_shell - runs the interactive shell.
 * @path: pointer to the list of dir of the PATH.
 * @env: environment variable.
 * @program_name: argv[0] of main.
 * @mode: specify whether to run in interactive or non-interactive mode.
 * Return: always 0 (success).
 */
int start_shell(list_t *path, char **env, char *program_name, int mode)
{
	char *buffer = NULL;
	int status, line_status;
	size_t len = 0;

	while (1)
	{
		if (mode == 1)
			write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
		signal(SIGINT, ctrl_c);
		line_status = getline(&buffer, &len, stdin);
		if (line_status == -1)
		{
			if (line_status == EOF)
			{
				free(buffer);
				if (mode == 1)
					write(STDOUT_FILENO, "\n", 1);
				return (status);
			}
			print_error(program_name, buffer, 3);
		}
		/* if buffer only contains spaces or the \n char will show prompt again */
		status = execute_buffer(buffer, path, env, program_name);
		if (status == -1 || status == 127 || status == 2)
		{
			if (status == -1)
				perror("COMMAND NOT FOUND");
			free(buffer);
			break;
		}
	}
	return (status);
}
