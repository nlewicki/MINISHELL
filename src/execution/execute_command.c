/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:59:19 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 11:38:38 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	nbr_of_args(char **str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (CD);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ENV);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (EXIT);
	else
		return (NONE);
}

void	exec_builtin(t_command *cmd, int builtin)
{
	int	argc;
	int	result;

	result = 0;
	argc = nbr_of_args(cmd->args);
	if (builtin == CD)
		result = ft_cd(cmd->args, argc);
	else if (builtin == PWD)
		result = pwd();
	else if (builtin == ECHO)
		result = ft_echo(cmd->args, argc);
	else if (builtin == ENV)
		result = env();
	else if (builtin == UNSET)
		result = ft_unset(cmd->args, argc);
	else if (builtin == EXPORT)
		result = ft_export(cmd->args, argc);
	else if (builtin == EXIT)
		result = ft_exit(cmd->args);
	*exit_status() = result;
}

int	execute_command(t_list *tabel)
{
	t_list	*tmp;
	int		builtin;
	int		result;

	tmp = tabel;
	builtin = is_builtin((t_command *)tmp->content);
	if (builtin)
		exec_builtin((t_command *)tmp->content, builtin);
	else
	{
		result = execute_external_command(((t_command *)tmp->content)->args);
		*exit_status() = result;
	}
	return (0);
}
