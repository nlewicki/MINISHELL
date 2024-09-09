/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:41:46 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/13 14:54:23 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	destlen;
	size_t	totallen;
	size_t	i;

	i = 0;
	srclen = 0;
	destlen = 0;
	while (src[srclen] != '\0')
		srclen++;
	while (dst[destlen] != '\0' && destlen < dstsize)
		destlen++;
	if (dstsize <= destlen)
		return (dstsize + srclen);
	i = destlen;
	totallen = destlen + srclen;
	while (src[i - destlen] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i - destlen];
		i++;
	}
	dst[i] = '\0';
	return (totallen);
}

// int main(void)
// {
// 	char dest[] = "hallo";
// 	char src[] = "welt";
// 	char src2[] = "welt";

// 	printf ("%zu\n", ft_strlcat(dest, src, sizeof(dest)));
// 	printf ("%lu\n", strlcat(dest, src2, sizeof(dest)));
// 	return (0);
// }
