/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:23:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 12:19:28 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	isspecials(char c)
{
	char	*specials;

	specials = "<>|\'\"";
	while (*specials)
	{
		if (c == *specials)
			return (true);
		specials++;
	}
	return (false);
}

void	trim_str(t_trim *trim, char *input)
{
	trim->i = 0;
	trim->j = 0;
	trim->is_space = false;
	trim->error = false;
	while (trim->j < trim->len)
	{
		if (isspecials(input[trim->i]))
		{
			handle_specials(trim, input);
			if (trim->error)
				break ;
		}
		else
			handle_non_specials(trim, input);
		trim->i++;
	}
	trim->result[trim->j] = '\0';
}

char	*trim_whitespace(char *input)
{
	t_trim	trim;

	input = ft_strtrim(input, " \t\n");
	if (!input)
		return (NULL);
	trim.len = ft_trim_len(input);
	trim.result = ft_calloc(sizeof(char), trim.len + 1);
	if (!trim.result)
		return (NULL);
	trim_str(&trim, input);
	if (trim.error == true)
		return (free(trim.result), NULL);
	free(input);
	return (trim.result);
}

void	*check_syntax(char *input)
{
	char	*error;

	error = handle_syntax_errors(input);
	if (error)
	{
		ft_putendl_fd(error, STDERR_FILENO);
		free(error);
		return (NULL);
	}
	return (input);
}

t_list	*parse_input(char *input)
{
	char	*new;
	char	**tokens;
	t_list	*list;

	list = NULL;
	new = trim_whitespace(input);
	if (!new)
		return (NULL);
	if (!check_syntax(new))
		return (free(new), NULL);
	tokens = split_space_quotes(new);
	free(new);
	if (!tokens)
		return (NULL);
	if (create_linked_list(tokens, &list))
	{
		free_token_array(tokens);
		ft_lstclear(&list, free_token);
		return (NULL);
	}
	free_token_array(tokens);
	return (list);
}
