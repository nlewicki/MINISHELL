/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:12:34 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/03 10:11:49 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


typedef enum {
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HERE,
	TOKEN_WORD,
}	t_token_type;

typedef struct s_token{
	t_token_type	type;
	char			*content;
} t_token;


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

static char	*extract_quoted_token(const char *str, size_t *pos, char quote)
{
	size_t	start;
	size_t	end;

	start = *pos + 1;
	end = start;
	while (str[end] && str[end] != quote)
		end++;
	*pos = end + 1;
	return (strndup(str + start, end - start));
}

static char	*extract_unquoted_token(const char *str, size_t *pos)
{
	size_t	start;
	size_t	end;

	start = *pos;
	end = start;
	while (str[end] && str[end] != ' ' && !is_quote(str[end]))
		end++;
	*pos = end;
	return (strndup(str + start, end - start));
}

static char	*extract_token(const char *str, size_t *pos)
{
	char	*token;

	if (is_quote(str[*pos]))
		token = extract_quoted_token(str, pos, str[*pos]);
	else
		token = extract_unquoted_token(str, pos);
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
	result = calloc(count + 1, sizeof(char *));
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

// int	main(void)
// {
// 	t_array	*tokens;
// 	size_t	i;

// 	i = 0;
// 	tokens = split_space_quotes("echo \"Hello, World!\" 'Goodbye, World!'");
// 	if (!tokens)
// 		return (1);
// 	while (i < tokens->count)
// 	{
// 		printf("Token %zu: %s\n", i, tokens->tokens[i]);
// 		i++;
// 	}
// 	free_token_array(tokens);
// 	system("leaks a.out");
// 	return (0);
// }
