/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:06:42 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/03 13:10:59 by nlewicki         ###   ########.fr       */
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
	if (input[trim->i] != '$')
		trim->result[trim->j++] = ' ';
}

void	handle_quotes(t_trim *trim, char *input)
{
	char quote;

	if (trim->j > 0 && (!isspace(trim->result[trim->j - 1])))
		trim->result[trim->j++] = ' ';
	quote = input[trim->i];
	trim->result[trim->j++] = input[trim->i++];
	while ((input[trim->i] != '\0') && (input[trim->i] != quote))
		trim->result[trim->j++] = input[trim->i++];
	if (input[trim->i] == quote)
	{
		trim->result[trim->j++] = input[trim->i];
			trim->result[trim->j++] = ' ';
	}
	else
	{
		printf("Missing closing quote\n");
		trim->error = true;
	}
}

void	handle_specials(t_trim *trim, char *input)
{
	char	tmp;

	if ((input[trim->i] == '\'') || (input[trim->i] == '\"'))
	{
		handle_quotes(trim, input);
		trim->is_space = true;
	}
	else if (input[trim->i] == '|' || input[trim->i] == '>'
		|| input[trim->i] == '<' || input[trim->i] == '$')
	{
		tmp = input[trim->i];
		handle_operator(trim, input);
		if (tmp == '$')
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
