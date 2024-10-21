/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:45:17 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/21 13:44:23 by nlewicki         ###   ########.fr       */
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

void	ft_errorcode_exit(char *command, char *path)
{
	ft_putstr_fd(command, 2);
	if (ft_strcmp(command, ".") == 0)
	{
		ft_putendl_fd(": filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", STDERR_FILENO);
		free(path);
		exit(2);
	}
	if (ft_strcmp(path, command) == 0 && !(ft_strncmp(command, "./",
				2) == 0 || ft_strncmp(command, "/", 1) == 0
			|| ft_strncmp(command, "../", 3) == 0))
		ft_putendl_fd(": command not found", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	free(path);
	if (errno == EACCES || errno == EISDIR)
		exit(126);
	exit(127);
}

static void	execute_child_process(char *command_path, char **args)
{
	if (*is_expanded() == 1)
	{
		exit(0);
	}
	execve(command_path, args, *env_vars());
	*exit_status() = 126;
	ft_errorcode_exit(args[0], command_path);
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
