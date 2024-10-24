/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:06:42 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/24 15:56:01 by mhummel          ###   ########.fr       */
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

static void	validate_operator(t_trim *trim, char *input, char op, int count)
{
	if (count == 2 && (op == '<' || op == '>'))
	{
		trim->result[trim->j++] = op;
		trim->result[trim->j++] = op;
		if (input[trim->i + 2] != '\0')
			trim->result[trim->j++] = ' ';
		trim->i++;
	}
	else
	{
		trim->result[trim->j++] = op;
		if (input[trim->i + 1] != '\0')
			trim->result[trim->j++] = ' ';
	}
}

void	handle_operator(t_trim *trim, char *input)
{
	int		count;
	char	op;

	op = input[trim->i];
	count = 1;
	while (input[trim->i + count] == op)
		count++;
	if ((op == '<' || op == '>') && count > 2)
	{
		trim->error = true;
		*exit_status() = 2;
		ft_putendl_fd("syntax error near unexpected token `<'", STDERR_FILENO);
		return ;
	}
	if (trim->j > 0 && (!ft_isspace(trim->result[trim->j - 1])))
		trim->result[(trim->j)++] = ' ';
	validate_operator(trim, input, op, count);
}

void	handle_quotes(t_trim *trim, char *input)
{
	char	quote;

	quote = input[trim->i];
	trim->result[trim->j++] = input[trim->i++];
	while ((input[trim->i] != '\0') && (input[trim->i] != quote))
		trim->result[trim->j++] = input[trim->i++];
	if (input[trim->i] == quote)
		trim->result[trim->j++] = input[trim->i];
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
