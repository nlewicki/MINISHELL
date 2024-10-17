/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:23:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/17 11:25:46 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isspecials(char c)
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
		else if (ft_isspace(input[trim->i]))
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
	printf("\ntrim_len: [%zu]\n\n", trim.len);
	trim.result = ft_calloc(sizeof(char), trim.len + 1);
	if (!trim.result)
		return (NULL);
	trim_str(&trim, input);
	if (trim.error == true)
		return (free(trim.result), NULL);
	printf("trimmed: [%s]			len: [%zu]\n", trim.result,
					ft_strlen(trim.result));
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
	printf("input:   [%s]\n", input);
	new = trim_whitespace(input);
	if (!new)
		return (NULL);
	if (!check_syntax(new))
		return (free(new), NULL);
	tokens = split_space_quotes(new);
	free(new);
	if (!tokens)
		return (NULL);
	printf("\n");
	for (size_t i = 0; tokens[i]; i++)      // debugg
		printf("token: [%s]\n", tokens[i]); // debugg
	if (create_linked_list(tokens, &list))
	{
		free_token_array(tokens);
		ft_lstclear(&list, free_token);
		return (NULL);
	}
	free_token_array(tokens);
	return (list);
}
