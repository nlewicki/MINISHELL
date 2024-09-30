/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:02:29 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/30 10:03:52 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_word(const char *word, bool *space_printed)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			single_quotes++;
		else if (word[i] == '"')
			double_quotes++;
		i++;
	}
	i = 0;
	while (word[i])
	{
		if ((word[i] == '\'' && single_quotes % 2 == 0)
			|| (word[i] == '"' && double_quotes % 2 == 0))
		{
			i++;
			continue ;
		}
		else
		{
			if (*space_printed)
			{
				printf(" ");
				*space_printed = false;
			}
			printf("%c", word[i]);
		}
		i++;
	}
}

int	ft_echo(char *argv[], int argc)
{
	int		i;
	int		j;
	bool	n_flag;
	bool	space_printed;

	i = 1;
	n_flag = false;
	space_printed = false;
	while (i < argc && argv[i][0] == '-' && argv[i][1] == 'n')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		n_flag = true;
		i++;
	}
	while (i < argc)
	{
		print_word(argv[i], &space_printed);
		space_printed = true;
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
