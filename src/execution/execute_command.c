/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:59:19 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/14 10:00:10 by nlewicki         ###   ########.fr       */
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

int	exec_builtin(t_command *cmd, int builtin)
{
	write(1, "Executing builtin\n\n", 19);
	if (builtin == CD)
		ft_cd(cmd->args, nbr_of_args(cmd->args));
	else if (builtin == PWD)
		pwd();
	else if (builtin == ECHO)
		ft_echo(cmd->args, nbr_of_args(cmd->args));
	else if (builtin == ENV)
		env();
	else if (builtin == UNSET)
		ft_unset(cmd->args, nbr_of_args(cmd->args));
	else if (builtin == EXPORT)
		ft_export(cmd->args, nbr_of_args(cmd->args));
	return (0);
}

int execute_command(t_list *tabel)
{
	t_list	*tmp;
	int		builtin;

	tmp = tabel;
	builtin = is_builtin((t_command *)tmp->content);
	if (builtin)
		exec_builtin((t_command *)tmp->content, builtin);
	else
		write(1, "Not a builtin\n", 14);
	return (0);
}
