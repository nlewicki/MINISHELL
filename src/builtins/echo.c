/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:02:29 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/27 09:27:57 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *argv[], int argc)
{
	int	i;
	int	j;
	int	n_flag;

	i = 0;
	n_flag = 0;
	while (++i < argc && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		n_flag = 1;
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
