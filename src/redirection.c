/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:16:29 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/19 13:43:18 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirections(char *input, t_redirection *redirections,
		int *redirection_count)
{
	char	*token;
	char	*saveptr;

	*redirection_count = 0;
	token = ft_strtok_r(input, " \t", &saveptr);
	while (token != NULL && *redirection_count < MAX_REDIRECTIONS)
	{
		if (ft_strcmp(token, "<") == 0)
			redirections[*redirection_count].type = 0;
		else if (ft_strcmp(token, ">") == 0)
			redirections[*redirection_count].type = 1;
		else if (ft_strcmp(token, "<<") == 0)
			redirections[*redirection_count].type = 2;
		else if (ft_strcmp(token, ">>") == 0)
			redirections[*redirection_count].type = 3;
		else
		{
			token = ft_strtok_r(NULL, " \t", &saveptr);
			continue ;
		}
		token = ft_strtok_r(NULL, " \t", &saveptr);
		if (token == NULL)
		{
			write(2, "Error: Missing argument for redirection\n", 39);
			return (1);
		}
		redirections[*redirection_count].file = ft_strdup(token);
		(*redirection_count)++;
		token = ft_strtok_r(NULL, " \t", &saveptr);
	}
	return (0);
}

int	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening input file"), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("Error redirecting input"), close(fd), 1);
	return (close(fd), 0);
}

int	redirect_output(char *file, int flags)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | flags, 0644);
	if (fd < 0)
		return (perror("Error opening output file"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	if (pipe(pipe_fd) < 0)
		return (perror("Error creating pipe"), 1);
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("Error redirecting input");
		close(pipe_fd[0]);
		return (1);
	}
	close(pipe_fd[0]);
	return (0);
}

int	apply_redirection(t_redirection *redirection)
{
	if (redirection->type == 0)
		return (redirect_input(redirection->file));
	if (redirection->type == 1)
		return (redirect_output(redirection->file, O_TRUNC));
	if (redirection->type == 2)
		return (handle_heredoc(redirection->file));
	if (redirection->type == 3)
		return (redirect_output(redirection->file, O_APPEND));
	return (0);
}

int	apply_redirections(t_redirection *redirections, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (apply_redirection(&redirections[i]))
			return (1);
		i++;
	}
	return (0);
}
