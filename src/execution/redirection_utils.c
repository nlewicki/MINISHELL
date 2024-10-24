/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:33:15 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/24 11:12:00 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std_fds(int orig_stdin, int orig_stdout)
{
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

int	is_redirection(char *symbol)
{
	return (ft_strcmp(symbol, "<") == 0 || ft_strcmp(symbol, ">") == 0
		|| ft_strcmp(symbol, ">>") == 0 || ft_strcmp(symbol, "<<") == 0);
}

static int	handle_heredoc_redirection(t_command *cmd, int *last_heredoc_fd,
		int i)
{
	if (*last_heredoc_fd != -1)
		close(*last_heredoc_fd);
	*last_heredoc_fd = handle_heredoc(cmd->filename[i]);
	if (*last_heredoc_fd == -1)
		return (1);
	return (0);
}

static int	finalize_heredoc(int last_heredoc_fd)
{
	if (last_heredoc_fd != -1)
	{
		if (dup2(last_heredoc_fd, STDIN_FILENO) == -1)
			return (close(last_heredoc_fd), 1);
		close(last_heredoc_fd);
	}
	return (0);
}

int	apply_redirections(t_command *cmd)
{
	int	i;
	int	last_heredoc_fd;

	i = 0;
	last_heredoc_fd = -1;
	while (cmd->red_symbol && cmd->red_symbol[i])
	{
		if (ft_strcmp(cmd->red_symbol[i], "<<") == 0)
		{
			if (handle_heredoc_redirection(cmd, &last_heredoc_fd, i))
				return (1);
		}
		else if (apply_single_redirection(cmd->red_symbol[i], cmd->filename[i]))
			return (1);
		i++;
	}
	return (finalize_heredoc(last_heredoc_fd));
}
