/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:05:50 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/18 10:05:55 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_expansion(char **result, char **start, char **end, char *src)
{
	*result = NULL;
	*start = src;
	*end = src;
}

static void	handle_quotes(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (c == '"')
		*in_double_quotes = !(*in_double_quotes);
}

static int	should_expand(char c, char next_c, int in_single_quotes)
{
	return (c == '$' && !in_single_quotes
		&& (ft_isalnum(next_c) || next_c == '_'));
}

static int	expand_variable(char **result, char **start, char **end)
{
	if (copy_until_dollar(result, *start, *end) == NULL)
		return (0);
	if (handle_dollar(result, start, end) == NULL)
		return (0);
	return (1);
}

char	*expand_env_variables(char *src)
{
	char	*result;
	char	*start;
	char	*end;
	int		in_single_quotes;
	int		in_double_quotes;

	init_expansion(&result, &start, &end, src);
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (*end)
	{
		handle_quotes(*end, &in_single_quotes, &in_double_quotes);
		if (should_expand(*end, *(end + 1), in_single_quotes))
		{
			if (!expand_variable(&result, &start, &end))
				return (NULL);
			continue;
		}
		end++;
	}
	if (*start && copy_until_dollar(&result, start, end) == NULL)
		return (NULL);
	if (result == NULL)
		result = ft_strdup(src);
	return (result);
}
