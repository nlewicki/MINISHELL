/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:12:34 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/15 12:36:21 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_array(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

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

static size_t	count_tokens(const char *str)
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
	char	quote = 0;

	start = *pos;
	end = start;
	while (str[end] && (str[end] != ' ' || quote != 0)) // Stop only at space if not in quotes
	{
		if (is_quote(str[end])) // Handle quotes inside token
		{
			if (quote == 0)
				quote = str[end]; // Opening a quote
			else if (quote == str[end])
				quote = 0; // Closing a quote
		}
		end++;
	}
	*pos = end;
	return (ft_strndup(str + start, end - start));
}

static char	*extract_token(const char *str, size_t *pos)
{
	char	*token;

	token = extract_token_2(str, pos);
	while (str[*pos] == ' ')
		(*pos)++;
	return (token);
}

static char	**init_result(const char *input)
{
	size_t	count;
	char	**result;

	if (!input)
		return (NULL);
	count = count_tokens(input);
	result = ft_calloc(count + 1, sizeof(char *));
	return (result);
}

static bool	fill_result(char **result, const char *input)
{
	size_t	pos;
	size_t	token_index;

	pos = 0;
	token_index = 0;
	while (input[pos])
	{
		while (input[pos] == ' ')
			pos++;
		if (input[pos])
		{
			result[token_index] = extract_token(input, &pos);
			if (!result[token_index])
				return (false);
			token_index++;
		}
	}
	return (true);
}

char	**split_space_quotes(const char *input)
{
	char	**result;

	result = init_result(input);
	if (!result)
		return (NULL);
	if (!fill_result(result, input))
	{
		free_token_array(result);
		return (NULL);
	}
	return (result);
}
