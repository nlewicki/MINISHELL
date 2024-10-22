/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:50:19 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 12:07:35 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_string(char *str, int start, int end)
{
	while (str[end])
	{
		str[start] = str[end];
		start++;
		end++;
	}
	str[start] = '\0';
}

static void	handle_double_quotes(char *str, int *i)
{
	int	start;
	int	end;

	start = *i;
	end = start + 1;
	while (str[end] && str[end] != '\"')
		end++;
	if (str[end] == '\"')
	{
		shift_string(str + start, 0, 1);
		shift_string(str + end - 1, 0, 1);
		*i = end - 2;
	}
	else
		*i = end;
}

static void	handle_single_quotes(char *str, int *i)
{
	int	start;
	int	end;

	start = *i;
	end = start + 1;
	while (str[end] && str[end] != '\'')
		end++;
	if (str[end] == '\'')
	{
		shift_string(str + start, 0, 1);
		shift_string(str + end - 1, 0, 1);
		*i = end - 2;
	}
	else
		*i = end;
}

static void	strip_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			handle_double_quotes(str, &i);
		else if (str[i] == '\'')
			handle_single_quotes(str, &i);
		i++;
	}
}

void	remove_quotes(t_command *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->args[i])
	{
		strip_quotes(cmd->args[i]);
		i++;
	}
}
