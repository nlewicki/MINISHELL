/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:03:52 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/24 09:43:48 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	setup_heredoc_delimiter(char **delimiter, bool *expand)
{
	size_t	len;
	char	*new_delim;

	*expand = true;
	len = ft_strlen(*delimiter);
	if (len > 1 && (*delimiter)[0] == '\'' && (*delimiter)[len - 1] == '\'')
	{
		*expand = false;
		new_delim = ft_strndup(*delimiter + 1, len - 2);
		*delimiter = new_delim;
		return (true);
	}
	return (false);
}

static int	process_heredoc_line(char *line, int pipe_fd, bool expand)
{
	char	*expanded_line;

	if (!expand)
	{
		ft_putendl_fd(line, pipe_fd);
		return (0);
	}
	expanded_line = expand_env_variables(line);
	if (!expanded_line)
		return (1);
	ft_putendl_fd(expanded_line, pipe_fd);
	free(expanded_line);
	return (0);
}

static int	read_heredoc_input(char *delimiter, int *pipe_fd, bool expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		if (process_heredoc_line(line, pipe_fd[1], expand))
			return (free(line), 1);
		free(line);
	}
}

static void	handle_single_heredoc(t_command *cmd, int pipe_fds[2], int *count,
		char *filename)
{
	bool	expand;
	bool	free_delim;
	char	*delimiter;

	delimiter = filename;
	free_delim = setup_heredoc_delimiter(&delimiter, &expand);
	if (read_heredoc_input(delimiter, pipe_fds, expand))
	{
		if (free_delim)
			free(delimiter);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return ;
	}
	if (free_delim)
		free(delimiter);
	close(pipe_fds[1]);
	cmd->heredoc_fds[*count] = pipe_fds[0];
	(*count)++;
}

void	process_heredocs(t_command *cmd, int *heredoc_count)
{
	int	i;
	int	pipe_fds[2];

	i = 0;
	while (cmd->red_symbol && cmd->red_symbol[i])
	{
		if (ft_strcmp(cmd->red_symbol[i], "<<") == 0)
		{
			if (pipe(pipe_fds) == -1)
				return ;
			handle_single_heredoc(cmd, pipe_fds, heredoc_count,
				cmd->filename[i]);
		}
		i++;
	}
}
