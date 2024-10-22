/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:06:42 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 12:18:06 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_non_specials(t_trim *trim, char *input)
{
	if (ft_isspace(input[trim->i]))
	{
		if (!trim->is_space && trim->j > 0)
		{
			trim->result[trim->j++] = ' ';
			trim->is_space = true;
		}
	}
	else
	{
		trim->result[trim->j++] = input[trim->i];
		trim->is_space = false;
	}
}

void	handle_operator(t_trim *trim, char *input)
{
	if (trim->j > 0 && (!ft_isspace(trim->result[trim->j - 1])))
		trim->result[(trim->j)++] = ' ';
	trim->result[(trim->j)++] = input[trim->i];
	if ((input[trim->i] == '<' && input[trim->i + 1] == '<')
		|| (input[trim->i] == '>' && input[trim->i + 1] == '>'))
	{
		trim->result[trim->j++] = input[trim->i + 1];
		if (input[trim->i + 2] != '\0')
			trim->result[trim->j++] = ' ';
		trim->i++;
		return ;
	}
	if (input[trim->i + 1] != '\0')
		trim->result[trim->j++] = ' ';
}

void	handle_quotes(t_trim *trim, char *input)
{
	char	quote;

	quote = input[trim->i];
	trim->result[trim->j++] = input[trim->i++];
	while ((input[trim->i] != '\0') && (input[trim->i] != quote))
		trim->result[trim->j++] = input[trim->i++];
	if (input[trim->i] == quote)
	{
		trim->result[trim->j++] = input[trim->i];
	}
	else
	{
		trim->error = true;
		printf("Error: Missing closing quote\n");
	}
}

void	handle_specials(t_trim *trim, char *input)
{
	if ((input[trim->i] == '\'') || (input[trim->i] == '\"'))
	{
		handle_quotes(trim, input);
		trim->is_space = false;
	}
	else if (input[trim->i] == '|' || input[trim->i] == '<'
		|| input[trim->i] == '>')
	{
		handle_operator(trim, input);
		trim->is_space = true;
	}
}

void	handle_history(char *input)
{
	if (g_signal == 0)
	{
		if (ft_strlen(input) > 0)
			add_history(input);
		else
			free(input);
	}
}
