/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:05:56 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/17 13:07:32 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *accept)
{
	const char	*s = str;
	const char	*a;

	while (*s)
	{
		a = accept;
		while (*a)
		{
			if (*s == *a)
			{
				break ;
			}
			a++;
		}
		if (*a == '\0')
		{
			return (s - str);
		}
		s++;
	}
	return (s - str);
}
