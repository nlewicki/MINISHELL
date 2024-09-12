/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:31:20 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/12 13:31:46 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_quotes(char *str)
{
	char	*end;
	char	*src;
	char	*dst;

	end = str;
	while (*end)
		end++;
	end--;
	if (end > str)
	{
		if ((str[0] == '"' && *end == '"')
			|| (str[0] == '\'' && *end == '\''))
		{
			src = str + 1;
			dst = str;
			while (src < end)
			{
				*dst = *src;
				dst++;
				src++;
			}
			*dst = '\0';
		}
	}
}

int	strcasecmp_custom(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
			return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
		s1++;
		s2++;
	}
	return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
}
