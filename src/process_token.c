/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:08:26 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/03 12:59:57 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

bool	command_exists(const char *command) // prototype
{
	char *path_env = getenv("PATH"); // Get the PATH environment variable
	if (!path_env)
	{
		return (false); // Return false if PATH is not set
	}
	char *path = strtok(path_env, ":"); // Split the PATH into directories
	while (path)
	{
		char command_path[512]; // Buffer to hold the full path of the command
		snprintf(command_path, sizeof(command_path), "%s/%s", path, command);
		struct stat buffer; // Structure to hold file information
		if (stat(command_path, &buffer) == 0)
		{
			if (buffer.st_mode & S_IXUSR)
			{                // Check if it's an executable
				return (true); // Command exists
			}
		}
		path = strtok(NULL, ":"); // Move to the next directory in PATH
	}
	return (false); // Command not found
}

void fill_struct(t_token *token, char *content)
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
	else if (ft_strncmp(content, "$", 1) == 0)
		token->type = TOKEN_VARIABLE;
	else if (command_exists(content))
		token->type = TOKEN_COMMAND;
	else
			token->type = TOKEN_WORD;
	token->content = ft_strdup(content);
}
