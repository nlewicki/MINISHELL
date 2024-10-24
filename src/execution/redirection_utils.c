/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:33:15 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/24 09:42:51 by mhummel          ###   ########.fr       */
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

void	print_redirection_error(char *filename, char *error_msg)
{
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
}

static int	handle_heredoc_redirection(t_command *cmd, int *heredoc_index)
{
	if (dup2(cmd->heredoc_fds[*heredoc_index], STDIN_FILENO) == -1)
		return (1);
	close(cmd->heredoc_fds[*heredoc_index]);
	(*heredoc_index)++;
	return (0);
}

int	apply_redirections(t_command *cmd)
{
	int	i;
	int	heredoc_index;
	int	heredoc_count;
	int	had_error;

	heredoc_count = 0;
	had_error = 0;
	process_heredocs(cmd, &heredoc_count);
	i = 0;
	heredoc_index = 0;
	while (cmd->red_symbol && cmd->red_symbol[i])
	{
		if (ft_strcmp(cmd->red_symbol[i], "<<") == 0)
			had_error = handle_heredoc_redirection(cmd, &heredoc_index);
		else if (ft_strcmp(cmd->red_symbol[i], "<") == 0)
			had_error = redirect_input(cmd->filename[i]);
		else if (redirect_output(cmd->filename[i], ft_strcmp(cmd->red_symbol[i],
					">>") == 0))
			had_error = 1;
		i++;
	}
	return (had_error);
}
