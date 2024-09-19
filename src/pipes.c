/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:47:35 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/19 12:45:11 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_piped_commands(char *commands[], int num_commands)
{
	pid_t	pid;
	int		i;
	int 	j;
	char	*args[MAX_ARGS];

	int status, pipefd[2], prev_pipe[2] = {-1, -1};
	i = 0;
	while (i < num_commands)
	{
		if (i < num_commands - 1)
		{
			if (pipe(pipefd) == -1)
				return (perror("pipe"), 1);
		}
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		else if (pid == 0)
		{
			if (i > 0)
			{
				dup2(prev_pipe[0], STDIN_FILENO);
				close(prev_pipe[0]);
				close(prev_pipe[1]);
			}
			if (i < num_commands - 1)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			parse_command(commands[i], args);
			execvp(args[0], args);
			perror("execvp");
			j = 0;
			while (args[j] != NULL)
			{
				free(args[j]);
				j++;
			}
			exit(EXIT_FAILURE);
		}
		else
		{
			if (i > 0)
			{
				close(prev_pipe[0]);
				close(prev_pipe[1]);
			}
			if (i < num_commands - 1)
			{
				prev_pipe[0] = pipefd[0];
				prev_pipe[1] = pipefd[1];
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
