/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:25:01 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/13 11:58:41 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	ptr = (const unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char	str[] = "http://www.tutorialspoint.com";
// 	const char	ch = 't';
// 	char		*ret;

// 	ret = memchr(str, ch, strlen(str));
// 	printf("String after: %c\nis:  %s\n", ch, ret);
// 	printf("Meins %s\n", ft_memchr(str, ch, 15));
// 	return(0);
// }
