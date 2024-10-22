/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:08:26 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 12:29:29 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <sys/stat.h>

static char	*create_command_path(const char *path, const char *command)
{
	char	*command_path;
	size_t	path_len;
	size_t	command_len;

	path_len = ft_strlen(path);
	command_len = ft_strlen(command);
	command_path = malloc(path_len + command_len + 2);
	if (!command_path)
		return (NULL);
	ft_strlcpy(command_path, path, path_len + 1);
	command_path[path_len] = '/';
	ft_strlcpy(command_path + path_len + 1, command, command_len + 1);
	return (command_path);
}

static bool	check_command_exists(const char *command_path)
{
	struct stat	buffer;

	if (stat(command_path, &buffer) == 0)
	{
		if (buffer.st_mode & S_IXUSR)
			return (true);
	}
	return (false);
}

static bool	search_command_in_path(char *path_copy, const char *command)
{
	char	*path;
	char	*command_path;
	bool	exists;

	path = ft_strtok(path_copy, ":");
	while (path)
	{
		command_path = create_command_path(path, command);
		if (!command_path)
			return (false);
		exists = check_command_exists(command_path);
		free(command_path);
		if (exists)
			return (true);
		path = ft_strtok(NULL, ":");
	}
	return (false);
}

bool	command_exists(const char *command)
{
	char	*path_env;
	char	*path_copy;
	bool	result;

	path_env = get_our_env("PATH");
	if (!path_env)
		return (false);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (false);
	result = search_command_in_path(path_copy, command);
	free(path_copy);
	return (result);
}

void	fill_struct(t_token *token, char *content)
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
		token->type = TOKEN_PIPE;
	else
		token->type = TOKEN_WORD;
	token->content = ft_strdup(content);
}
