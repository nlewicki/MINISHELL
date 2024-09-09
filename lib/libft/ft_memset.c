/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:58:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/12 12:18:32 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t num)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = str;
	i = 0;
	while (i < num)
	{
		ptr[i] = (unsigned char)value;
		i++;
	}
	return (str);
}

// int	main(void)
// {
// 	char str[] = "Hello, world!";
// 	size_t num = 5;
// 	int value = 'A';
// 	printf("%s\n", str);
// 	ft_memset(str, value, num);
// 	printf("%s\n", str);

// 	return 0;
// }
