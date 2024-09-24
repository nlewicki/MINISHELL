/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:45:17 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/24 10:50:56 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_PATH 1024

static int is_directory(const char *path)
{
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
		return 0;
	return (S_ISDIR(statbuf.st_mode));
}

char	*search_path(const char *file)
{
	char	*path;
	char	*path_copy;
	char	*dir;
	char	full_path[MAX_PATH];
	char	**envp;

	path = NULL;
	envp = *env_vars();
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (NULL);
	dir = ft_strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, file);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (ft_strdup(full_path));
		}
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

int	execute_external_command(char **args)
{
	char	*command_path;
	pid_t	pid;
	int		status;

	if (args[0][0] == '$')
	{
		char *expanded = expand_env_variables(args[0], 0);
		if (expanded)
		{
			printf("%s\n", expanded);
			free(expanded);
			return 0;
		}
		else
		{
			printf("\n");
			return 0;
		}
	}
	if (args[0][0] == '/' || args[0][0] == '.')
		command_path = args[0];
	else
		command_path = search_path(args[0]);
	if (!command_path)
		return (127);
	if (is_directory(command_path))
    {
        printf("%s: is a directory\n", command_path);
        if (command_path != args[0])
            free(command_path);
        return 126;
    }
	pid = fork();
	if (pid == 0)
	{
		execve(command_path, args, *env_vars());
		perror(args[0]);
		exit(126);
	}
	else if (pid < 0)
	{
		perror("fork");
		if (command_path != args[0])
			free(command_path);
		return (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (command_path != args[0])
			free(command_path);
		return (WEXITSTATUS(status));
	}
}
