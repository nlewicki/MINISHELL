/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:12:34 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/15 09:57:15 by nlewicki         ###   ########.fr       */
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

static size_t	calculate_token_length(const char *str, size_t *start,
		char *quote)
{
	size_t	end;
	size_t	token_len;

	end = *start;
	token_len = 0;
	*quote = 0;
	while (str[end] && (str[end] != ' ' || *quote != 0))
	{
		if (is_quote(str[end]))
		{
			if (*quote == 0)
				*quote = str[end];
			else if (*quote == str[end])
				*quote = 0;
		}
		else
			token_len++;
		end++;
	}
	*start = end;
	return (token_len);
}

static void	copy_token_without_quotes(const char *str, size_t *start,
		size_t end, char *token)
{
	size_t	i;
	char	quote;

	quote = 0;
	i = 0;
	while (*start < end)
	{
		if (is_quote(str[*start]))
		{
			if (quote == 0)
				quote = str[*start];
			else if (quote == str[*start])
				quote = 0;
		}
		else
			token[i++] = str[*start];
		(*start)++;
	}
	token[i] = '\0';
}

static char	*extract_token_2(const char *str, size_t *pos)
{
	size_t	token_len;
	char	*token;
	char	quote;
	size_t	start;

	quote = 0;
	start = *pos;
	token_len = calculate_token_length(str, &start, &quote);
	token = (char *)malloc(token_len + 1);
	if (!token)
		return (NULL);
	copy_token_without_quotes(str, pos, start, token);
	*pos = start;
	return (token);
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
