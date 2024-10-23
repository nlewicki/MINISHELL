/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:10:53 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/23 12:35:47 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_strcmp(path, command) == 0 && !(ft_strncmp(command, "./", 2) == 0
			|| ft_strncmp(command, "/", 1) == 0 || ft_strncmp(command, "../",
				3) == 0))
		ft_putendl_fd(": command not found", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(ft_strerror(errno), 2);
	}
	free(path);
	if (errno == EACCES || errno == EISDIR)
		exit(126);
	exit(127);
}

int	handle_command_not_found(char **args)
{
	ft_putstr_fd(args[0], 2);
	ft_putendl_fd(": command not found", 2);
	*exit_status() = 127;
	return (127);
}

int	handle_parent_process(pid_t pid, char *command_path)
{
	int	status;

	free(command_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
