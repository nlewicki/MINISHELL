/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:23:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/14 12:59:40 by mhummel          ###   ########.fr       */
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
	// printf("result: %s\n", trim.result);
	new = ft_strtrim(trim.result, " \t\f\n\v\r");
	if (!new)
		return (NULL);
	// printf("trimmed: %s\n", new);
	return (new);
}

t_list *parse_input(char *input)
{
    char *new;
    char **tokens;
    t_list *list;
    t_list *tabel;

    list = NULL;
    tabel = NULL;
    new = trim_whitespace(input);
    if (!new)
        return (NULL);

    // Expand environment variables
    char *expanded = expand_env_variables(new, 0);
    free(new);
    if (!expanded)
        return (NULL);

    tokens = split_space_quotes(expanded);
    free(expanded);
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

