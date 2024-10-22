/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:12:34 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/22 12:34:36 by nlewicki         ###   ########.fr       */
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
