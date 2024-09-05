/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:52:59 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/13 11:58:47 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	ptrs1 = (unsigned char *)str1;
	ptrs2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (ptrs1[i] != ptrs2[i])
			return (ptrs1[i] - ptrs2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char str1[] = "ABCD";
// 	char str2[] = "ABCD";

// 	printf ("%d\n", memcmp(str1, str2, 5));
// 	printf ("%d\n", ft_memcmp(str1, str2, 5));
// 	return(0);
// }
