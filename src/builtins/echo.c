/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:02:29 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/03 11:22:07 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *argv[], int argc)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (argc > 1 && strcmp(argv[1], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
