#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * main - simple shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables
 * Return: 0
 */

int main(int argc __attribute__((unused)), char *argv[], char *envp[])
{
	char *line = NULL;
	int *status = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;

	while (1)
	{
		printf("simple-shell> ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			break;
		}
		line[read - 1] = '\0';
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
		{
			execve(line, argv, envp);
			perror("simple-shell");
			exit(0);
		}
		wait(status);
	}

	free(line);
	return (0);
}
