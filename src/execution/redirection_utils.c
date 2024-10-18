/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:33:15 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/18 13:42:31 by mhummel          ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
}

int	apply_single_redirection(char *symbol, char *filename)
{
	if (ft_strcmp(symbol, "<") == 0)
		return (redirect_input(filename));
	else if (ft_strcmp(symbol, ">") == 0)
		return (redirect_output(filename, 0));
	else if (ft_strcmp(symbol, ">>") == 0)
		return (redirect_output(filename, 1));
	else if (ft_strcmp(symbol, "<<") == 0)
		return (handle_heredoc(filename));
	return (0);
}

int	apply_redirections(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->red_symbol && cmd->red_symbol[i])
	{
		if (apply_single_redirection(cmd->red_symbol[i], cmd->filename[i]))
			return (1);
		i++;
	}
	return (0);
}
