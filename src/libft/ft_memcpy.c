/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:05:40 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/18 11:43:58 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*ptrs;
	unsigned char		*ptrd;

	ptrs = src;
	ptrd = dest;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i != n)
	{
		ptrd[i] = ptrs[i];
		i++;
	}
	return (dest);
}

// int	main (void)
// {
// 	const char	src[50] = "Hello, World123";
// 	char	dest[50];
// 	strcpy(dest,"Heloooo!!");
// 	printf("Before memcpy dest = %s\n", dest);
// 	memcpy(dest, src, 7);
// 	printf("After memcpy dest = %s\n", dest);

// 	const char	src2[50] = "Hello, World123";
// 	char	dest2[50];
// 	ft_memcpy(dest2, src2, 7);
// 	printf("After ft_memcpy = %s\n", dest);
// 	return(0);
// }
