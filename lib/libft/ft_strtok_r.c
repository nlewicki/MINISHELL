/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:02:45 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/17 13:10:41 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char	*start;
	char	*end;

	if (str == NULL)
		str = *saveptr;
	start = str + ft_strspn(str, delim);
	if (*start == '\0')
	{
		*saveptr = start;
		return (NULL);
	}
	end = start + ft_strcspn(start, delim);
	if (*end != '\0')
	{
		*end = '\0';
		*saveptr = end + 1;
	}
	else
	{
		*saveptr = end;
	}
	return (start);
}
