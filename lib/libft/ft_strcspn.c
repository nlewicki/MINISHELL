/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:07:50 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/17 13:08:42 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *str, const char *reject)
{
	const char	*s = str;
	const char	*r;

	while (*s)
	{
		r = reject;
		while (*r)
		{
			if (*s == *r)
			{
				return (s - str);
			}
			r++;
		}
		s++;
	}
	return (s - str);
}
