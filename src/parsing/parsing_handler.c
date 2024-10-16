/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:06:42 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/16 13:00:40 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_operator(t_trim *trim, char *input)
{
	if (trim->j > 0 && !isspace(trim->result[trim->j - 1]))
		trim->result[trim->j++] = ' ';
	trim->result[trim->j++] = input[trim->i];
	if ((input[trim->i] == '<' && input[trim->i + 1] == '<')
		|| (input[trim->i] == '>' && input[trim->i + 1] == '>'))
		trim->result[trim->j++] = input[++trim->i];
	trim->i++;
	if (isspace(input[trim->i]))
	{
		trim->result[trim->j++] = ' ';
		trim->is_space = true;
	}
	else
		trim->is_space = false;
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
		trim->i++;
	}
	else
	{
		printf("Missing closing quote\n");
		trim->error = true;
	}
}

void	handle_specials(t_trim *trim, char *input)
{
	if ((input[trim->i] == '\'') || (input[trim->i] == '\"'))
	{
		handle_quotes(trim, input);
		trim->is_space = false;
	}
	else if (isspecials(input[trim->i]) || input[trim->i] == '$')
	{
		handle_operator(trim, input);
		if (input[trim->i - 1] == '$')
			trim->is_space = false;
		else
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
