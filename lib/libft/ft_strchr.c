/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:50:39 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/15 13:43:00 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}

// int	main(void)
// {
// 	const char str[] = "http://www.tutorialspoint.com";
// 	const char ch = '.';
// 	char *ret;
// 	char *my;

// 	ret = strchr(str, ch);
// 	printf("String after :%c is -  %s\n", ch, ret);
// 	my = ft_strchr(str, ch);
// 	printf("String after :%c is -  %s\n", ch, my);
// 	return(0);
// }
