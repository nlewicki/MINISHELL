/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:40:05 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/12 12:19:21 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = s;
	i = 0;
	if (n == 0)
		return ;
	while ((i < n) && (n > 0))
	{
		ptr[i] = '\0';
		i++;
	}
}

// int	main(void)
// {
// 	char s2[30] = "Hallo, welt";
// 	size_t num = 3;
// 	char s3[] = "Hallo, welt";

// 	printf("origin: %s\n", s2);
// 	bzero(s2, num);
// 	printf("changed: %s\n\n", s2);

// 	ft_bzero(s3, num);
// 	printf("changed: %s\n", s3);
// }
