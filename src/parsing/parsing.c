/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:23:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/15 09:15:10 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isspecials(char c)
{
	char	*specials;

	specials = "<>|$";
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
	while (trim->i < trim->len)
	{
		if (isspecials(input[trim->i]))
			handle_specials(trim, input);
		else if (isspace(input[trim->i]))
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
	char	*new;

	trim.len = ft_strlen(input);
	trim.result = ft_calloc(sizeof(char), trim.len + 100);
	if (!trim.result)
	{
		return (NULL);
	}
	trim_str(&trim, input);
	if (trim.error == true)
	{
		free(trim.result);
		return (NULL);
	}
	printf("result: %s\n", trim.result);
	new = ft_strtrim(trim.result, " \t\f\n\v\r");
	if (!new)
		return (NULL);
	printf("trimmed: %s\n", new);
	return (new);
}

t_list	*parse_input(char *input)
{
	char	*new;
	char	**tokens;
	t_list	*list;
	t_list	*tabel;

	tabel = NULL;
	list = NULL;
	printf("input: %s\n", input);
	new = trim_whitespace(input);
	if (!new)
		return (NULL);
	tokens = split_space_quotes(new); // split_space_quotes aber lass die quotes drin
	free(new);
	if (!tokens)
		return (NULL);
	for (size_t i = 0; tokens[i]; i++) // debugg
		printf("token: %s\n", tokens[i]); // debugg
	if (create_linked_list(tokens, &list))
	{
		free_token_array(tokens);
		ft_lstclear(&list, free_token);
		return (NULL);
	}
	free_token_array(tokens);
	return (list);
}

