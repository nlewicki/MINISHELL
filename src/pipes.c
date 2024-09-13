/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:47:35 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/13 09:58:57 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_piped_commands(char *commands[], int num_commands)
{
	pid_t	pid;
	int		in_fd;
	int		i;
	char	*args[MAX_ARGS];
	int		arg_count;

	int status, pipefd[2];
	in_fd = STDIN_FILENO;
	i = 0;
	while (i < num_commands)
	{
		if (i < num_commands - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				return (1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
		{
			if (in_fd != STDIN_FILENO)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (i < num_commands - 1)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			arg_count = parse_command(commands[i], args);
			execute_command(args, arg_count);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			if (i < num_commands - 1)
			{
				close(pipefd[1]);
				in_fd = pipefd[0];
			}
			else
				waitpid(pid, &status, 0);
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (WEXITSTATUS(status));
}
