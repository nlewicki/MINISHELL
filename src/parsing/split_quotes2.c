/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:33:12 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 12:35:02 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static void	update_token_state(char c, char *quote, bool *in_token,
		size_t *count)
{
	if (is_quote(c))
	{
		if (*quote == 0)
		{
			*quote = c;
			if (!*in_token)
			{
				(*count)++;
				*in_token = true;
			}
		}
		else if (*quote == c)
			*quote = 0;
	}
	else if (c == ' ' && *quote == 0)
		*in_token = false;
	else if (!*in_token)
	{
		(*count)++;
		*in_token = true;
	}
}

size_t	count_tokens(const char *str)
{
	size_t	count;
	size_t	i;
	bool	in_token;
	char	quote;

	count = 0;
	i = 0;
	in_token = false;
	quote = 0;
	while (str[i])
	{
		update_token_state(str[i], &quote, &in_token, &count);
		i++;
	}
	return (count);
}

static char	*extract_token_2(const char *str, size_t *pos)
{
	size_t	start;
	size_t	end;
	char	quote;

	quote = 0;
	start = *pos;
	end = start;
	while (str[end] && (str[end] != ' ' || quote != 0))
	{
		if (is_quote(str[end]))
		{
			if (quote == 0)
				quote = str[end];
			else if (quote == str[end])
				quote = 0;
		}
		end++;
	}
	*pos = end;
	return (ft_strndup(str + start, end - start));
}

char	*extract_token(const char *str, size_t *pos)
{
	char	*token;

	token = extract_token_2(str, pos);
	while (str[*pos] == ' ')
		(*pos)++;
	return (token);
}
