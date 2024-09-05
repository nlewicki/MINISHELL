/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:38:50 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/05 12:45:46 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token = NULL;
	char		*token_start;

	if (str == NULL)
		str = last_token;
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
	{
		last_token = str;
		return (NULL);
	}
	token_start = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	if (*str)
	{
		*str = '\0';
		last_token = str + 1;
	}
	else
		last_token = str;
	return (token_start);
}
