/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:20:21 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/16 10:50:02 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_spaces(const char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

static char	*get_error_message(char op)
{
	if (op == '|')
		return (ft_strdup("syntax error near unexpected token '|'"));
	if (op == ';')
		return (ft_strdup("syntax error near unexpected token ';'"));
	if (op == '\0')
		return (ft_strdup("syntax error near unexpected token `newline'"));
	return (ft_strdup("syntax error near unexpected token `newline'"));
}

static char	*check_operator(const char *input, int *i, int is_start)
{
	char	op;

	op = input[*i];
	if (is_start && (op == '|' || op == ';'))
		return (get_error_message(op));
	(*i)++;
	if ((op == '>' && input[*i] == '>') || (op == '<' && input[*i] == '<')
		|| (op == '|' && input[*i] == '|'))
		(*i)++;
	*i = skip_spaces(input, *i);
	if ((op == ';' || op == '|') && (input[*i] == '|' || input[*i] == ';'
			|| input[*i] == '>' || input[*i] == '<'))
		return (get_error_message(input[*i]));
	if (input[*i] == '\0')
	{
		if (op == '|')
			return (get_error_message('\0'));
		if (op == '>' || op == '<')
			return (get_error_message('\0'));
	}
	return (NULL);
}

char	*handle_syntax_errors(const char *input)
{
	int		i;
	char	*error;
	int		last_non_space;

	i = 0;
	last_non_space = -1;
	if (input[i] == '\0')
		return (NULL);
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			last_non_space = i;
		if (input[i] == '|' || input[i] == ';' || input[i] == '>'
			|| input[i] == '<')
		{
			error = check_operator(input, &i, i == 0);
			if (error)
				return (error);
		}
		else
			i++;
	}
	if (last_non_space != -1 && input[last_non_space] == '|')
		return (get_error_message('|'));
	return (NULL);
}
