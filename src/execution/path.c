/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:45:17 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/18 11:13:07 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_dir_for_command(const char *dir, const char *command)
{
	char	*full_path;

	full_path = ft_strjoin3(dir, "/", command);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_path(const char *command, char *path_env)
{
	char	*path_copy;
	char	*dir;
	char	*result;

	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		result = check_dir_for_command(dir, command);
		if (result)
		{
			free(path_copy);
			return (result);
		}
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

static char	*find_command_path(const char *command)
{
	char	*path_env;

	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	path_env = get_our_env("PATH");
	if (!path_env)
		return (NULL);
	return (search_in_path(command, path_env));
}

static void	execute_child_process(char *command_path, char **args)
{
	execve(command_path, args, *env_vars());
	perror("execve");
	free(command_path);
	exit(126);
}

int	execute_external_command(char **args)
{
	char	*command_path;
	pid_t	pid;

	command_path = find_command_path(args[0]);
	if (!command_path)
		return (handle_command_not_found(args));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		return (1);
	}
	if (pid == 0)
		execute_child_process(command_path, args);
	return (handle_parent_process(pid, command_path));
}
