/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:19:54 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/12 12:18:35 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	unsigned char	*ptrs;
	unsigned char	*ptrd;
	size_t			i;

	ptrs = (unsigned char *)str2;
	ptrd = (unsigned char *)str1;
	if (ptrd < ptrs)
	{
		i = 0;
		while (i < n)
		{
			ptrd[i] = ptrs[i];
			i++;
		}
	}
	else if (ptrd > ptrs)
	{
		i = n;
		while (i > 0)
		{
			ptrd[i - 1] = ptrs[i - 1];
			i--;
		}
	}
	return (str1);
}

// int	main (void)
// {
// 	const char	src[] = "Hello, World123";
// 	char	dest[] = "hellooooo!!";
// 	printf("Before memmove dest = %s\n", dest);
// 	printf("%s\n", memmove(dest, src, 7));

// 	const char	src2[] = "Hello, World123";
// 	char	dest2[] = "hellooooo!!";
// 	printf("%s\n", ft_memmove(dest2, src2, 7));
// 	return(0);
// }
