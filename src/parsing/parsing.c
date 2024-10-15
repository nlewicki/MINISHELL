/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:23:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/15 13:32:51 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isspecials(char c)
{
	char	*specials;

	specials = "<>|\'\"$";
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
	trim->is_space = true;
	trim->error = false;
	while (input[trim->i] && trim->j < trim->len)
	{
		if (isspecials(input[trim->i]))
			handle_specials(trim, input);
		else if (isspace(input[trim->i]))
		{
			if (!trim->is_space && trim->j > 0 && trim->j < trim->len - 1)
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

static int	ft_trim_len(char *input)
{
	int	i;
	int	len;
	int	last_was_space;

	i = 0;
	len = 0;
	last_was_space = 1;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
		{
			len++;
			last_was_space = 0;
		}
		else if (!last_was_space)
		{
			len++;
			last_was_space = 1;
		}
		if (input[i] == '<' || input[i] == '>' || input[i] == '|'
			|| input[i] == '$')
			len++;
		i++;
	}
	return (len);
}

char	*trim_whitespace(char *input)
{
	t_trim	trim;

	trim.len = ft_trim_len(input);
	printf("len: %zu\n", trim.len);
	trim.result = ft_calloc(sizeof(char), trim.len + 1);
	if (!trim.result)
		return (NULL);
	trim_str(&trim, input);
	if (trim.error == true)
		return (free(trim.result), NULL);
	printf("result: %s\n", trim.result);
	return (trim.result);
}

t_list	*parse_input(char *input)
{
	char	*new;
	char	**tokens;
	t_list	*list;
	t_list	*tabel;
	char	*error;

	tabel = NULL;
	list = NULL;
	printf("input: %s\n", input);
	new = trim_whitespace(input);
	if (!new)
		return (NULL);
	tokens = split_space_quotes(new);
	// split_space_quotes aber lass die quotes drin
	free(new);
	if (!tokens)
		return (NULL);
	for (size_t i = 0; tokens[i]; i++)    // debugg
		printf("token: %s\n", tokens[i]); // debugg
	// handle_syntax_error(tokens);
	if (create_linked_list(tokens, &list))
	{
		free_token_array(tokens);
		ft_lstclear(&list, free_token);
		return (NULL);
	}
	free_token_array(tokens);
	error = handle_syntax_errors(input);
	if (error)
	{
		ft_putendl_fd(error, STDERR_FILENO);
		free(error);
		ft_lstclear(&list, free_token);
		return (NULL);
	}
	return (list);
}
