/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:50:19 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/18 09:50:23 by nlewicki         ###   ########.fr       */
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
	int start = *i;
	int end = start + 1;

	// Find closing double quote
	while (str[end] && str[end] != '\"')
		end++;

	// If we found a closing double quote
	if (str[end] == '\"')
	{
		// Remove both opening and closing double quotes
		shift_string(str + start, 0, 1);         // Remove opening "
		shift_string(str + end - 1, 0, 1);       // Remove closing "
		*i = end - 2;  // Update position (adjusted for removed quotes)
	}
	else
	{
		*i = end; // If no closing double quote, just move the pointer to end
	}
}

static void	handle_single_quotes(char *str, int *i)
{
	int start = *i;
	int end = start + 1;

	// Find closing single quote
	while (str[end] && str[end] != '\'')
		end++;

	// If we found a closing single quote
	if (str[end] == '\'')
	{
		// Remove both opening and closing single quotes
		shift_string(str + start, 0, 1);         // Remove opening '
		shift_string(str + end - 1, 0, 1);       // Remove closing '
		*i = end - 2;  // Update position (adjusted for removed quotes)
	}
	else
	{
		*i = end; // If no closing single quote, just move the pointer to end
	}
}

void	strip_quotes(char *str)
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

void	remove_quotes(t_list *tabel)
{
	t_list		*tmp;
	t_command	*cmd;
	size_t		i;

	tmp = tabel;
	while (tmp)
	{
		cmd = tmp->content;
		i = 0;
		while (cmd->args[i])
		{
			strip_quotes(cmd->args[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
