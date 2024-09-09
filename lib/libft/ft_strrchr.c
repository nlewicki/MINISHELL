/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:17:48 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/15 13:37:07 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
// int	main (void)
// {
// 	const char str[] = "http://www.tutorialspoint.com";
// 	const char ch = 'h';
// 	char *ret;
// 	char *my;

// 	ret = strrchr(str, ch);
// 	printf("String after :%c is -  %s\n", ch, ret);
// 	my = ft_strrchr(str, ch);
// 	printf("String after :%c is -  %s\n", ch, my);
// 	return(0);
// }
