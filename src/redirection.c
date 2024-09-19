/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:16:29 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/19 13:06:07 by mhummel          ###   ########.fr       */
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

int	apply_redirections(t_redirection *redirections, int redirection_count)
{
	int		fd;
	int		pipe_fd[2];
	char	*line;
	size_t	len;
	ssize_t	read;
	int		i;

	i = 0;
	while (i < redirection_count)
	{
		switch (redirections[i].type)
		{
		case 0:
		{
			fd = open(redirections[i].file, O_RDONLY);
			if (fd < 0)
			{
				perror("Error opening input file");
				return (1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("Error redirecting input");
				close(fd);
				return (1);
			}
			close(fd);
		}
		break ;
		case 1:
		{
			fd = open(redirections[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("Error opening output file");
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		break ;
		case 2:
		{
			if (pipe(pipe_fd) < 0)
			{
				perror("Error creating pipe");
				return (1);
			}
			line = NULL;
			len = 0;
			while ((read = getline(&line, &len, stdin)) != -1)
			{
				if (ft_strcmp(line, redirections[i].file) == 0)
				{
					break ;
				}
				write(pipe_fd[1], line, read);
			}
			free(line);
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		}
		break ;
		case 3:
		{
			fd = open(redirections[i].file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (fd < 0)
			{
				perror("Error opening output file for appending");
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		break ;
		}
		i++;
	}
	return (0);
}
