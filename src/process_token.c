/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:08:26 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/03 13:55:30 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <sys/stat.h>

bool	command_exists(const char *command) // prototype
{
	char *path_env;
	char *path_copy;
	char *path;
	char command_path[PATH_MAX];
	int written;
	struct stat buffer;

	path_env = get_our_env("PATH");
	if (!path_env)
		return (false);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (false);
	path = ft_strtok(path_copy, ":");
	while (path)
	{
		written = snprintf(command_path, sizeof(command_path), "%s/%s", path,
				command);
		if (written < 0 || (size_t)written >= sizeof(command_path))
		{
			path = ft_strtok(NULL, ":");
			continue ;
		}
		if (stat(command_path, &buffer) == 0)
		{
			if (buffer.st_mode & S_IXUSR)
			{
				free(path_copy);
				return (true);
			}
		}
		path = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (false);
}

void	fill_struct(t_token *token, char *content, bool *command)
{
	if (!token || !content)
		return ;
	if (ft_strncmp(content, ">>", 2) == 0)
		token->type = TOKEN_REDIR_APPEND;
	else if (ft_strncmp(content, ">", 1) == 0)
		token->type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(content, "<<", 2) == 0)
		token->type = TOKEN_REDIR_HERE;
	else if (ft_strncmp(content, "<", 1) == 0)
		token->type = TOKEN_REDIR_IN;
	else if (ft_strncmp(content, "|", 1) == 0)
	{
		*command = false;
		token->type = TOKEN_PIPE;
	}
	else if (ft_strncmp(content, "$", 1) == 0)
		token->type = TOKEN_VARIABLE;
	else if (command_exists(content) && !*command)
	{
		*command = true;
		token->type = TOKEN_COMMAND;
	}
	else
		token->type = TOKEN_WORD;
	token->content = ft_strdup(content);
}
