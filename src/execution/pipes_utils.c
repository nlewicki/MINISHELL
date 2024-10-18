/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:56:42 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/18 12:51:03 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_child_pipes(int pipe_fds[][2], int i, int num_commands)
{
	if (i > 0)
	{
		if (dup2(pipe_fds[i - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
	}
	if (i < num_commands - 1)
	{
		if (dup2(pipe_fds[i][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
	}
	return (0);
}

static int	execute_single_command(t_command *cmd)
{
	int	builtin;

	builtin = is_builtin(cmd);
	if (builtin)
		exec_builtin(cmd, builtin);
	else
		return (execute_external_command(cmd->args));
	return (0);
}

int	fork_and_execute(int pipe_fds[][2], t_list *current, int i,
		int num_commands)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (setup_child_pipes(pipe_fds, i, num_commands))
			exit(1);
		close_pipes(pipe_fds, num_commands - 1);
		exit(execute_single_command((t_command *)current->content));
	}
	return (0);
}

int	wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
