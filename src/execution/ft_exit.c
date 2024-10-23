/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:38:59 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/23 11:42:09 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	calculate_exit(int *exit_code, char *args[])
{
	*exit_code = ft_atoi(args[1]);
	*exit_code = *exit_code % 256;
	*exit_status() = *exit_code;
}

int	ft_exit(char *args[])
{
	int	exit_code;

	exit_code = 0;
	if (args[1] != NULL)
	{
		if (!ft_atoi(args[1]) || ft_strlen(args[1]) == 0)
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			*exit_status() = 255;
			return (255);
		}
		if (args[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			*exit_status() = 1;
			return (1);
		}
		else
			calculate_exit(&exit_code, args);
	}
	exit_code = *exit_status();
	free_env(*env_vars());
	clear_shell_history();
	exit(exit_code);
}
