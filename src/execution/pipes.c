/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 09:47:35 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/18 12:50:19 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipes(int pipe_fds[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			perror("pipe");
			return (1);
		}
		i++;
	}
	return (0);
}

void	close_pipes(int pipe_fds[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}

int	execute_piped_commands(t_list *command_list)
{
	int		pipe_fds[MAX_ARGS - 1][2];
	int		num_commands;
	int		i;
	t_list	*current;

	num_commands = ft_lstsize(command_list);
	if (create_pipes(pipe_fds, num_commands - 1))
		return (1);
	i = 0;
	current = command_list;
	while (current)
	{
		if (fork_and_execute(pipe_fds, current, i, num_commands))
			return (close_pipes(pipe_fds, num_commands - 1), 1);
		current = current->next;
		i++;
	}
	close_pipes(pipe_fds, num_commands - 1);
	return (wait_for_children());
}
