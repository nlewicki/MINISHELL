/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:57:57 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/13 14:48:48 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while ((i < dstsize - 1) && (src[i] != '\0'))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}
// int	main(void)
// {
// 	char dest[15];
// 	const char *src = "lorem ipsum dolor sit amet";
// 	const char *src2 = "lorem ipsum dolor sit amet";

// 	printf("Destination string: %zu\n", ft_strlcpy(dest, src, 26));
// 	printf("what it should print: %zu\n", strlcpy(dest, src2, 26));
// 	return (0);
// }
