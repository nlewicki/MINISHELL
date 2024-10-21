/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:38:59 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/21 10:05:11 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *args[])
{
	int	exit_code;

	exit_code = 0;
	if (args[1] != NULL)
	{
		if (!ft_atoi(args[1]) || ft_strlen(args[1]) == 0)
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			*exit_status() = 255;
			exit(*exit_status());
		}
		if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			*exit_status() = 1;
			exit(*exit_status());
		}
		exit_code = ft_atoi(args[1]);
		exit_code = exit_code % 256;
		*exit_status() = exit_code;
	}
	exit_code = *exit_status();
	// ft_putendl_fd("exit", 2);
	// printf("exit code: %d\n", exit_code);
	exit(exit_code);
}
