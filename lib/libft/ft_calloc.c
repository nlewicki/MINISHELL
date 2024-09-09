/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:10:04 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/12 12:19:09 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	size_t			total_size;
	unsigned char	*ptr;

	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}
// int main(void)
// {
// 	int		*arr;
// 	size_t	n;
// 	size_t	i;

// 	n = 10;
// 	i = 0;
// 	arr = (int *)ft_calloc(n, sizeof(int));
// 	if (arr == NULL)
// 	{
// 		printf("Failed.\n");
// 		return (1);
// 	}
// 	printf("The value of the arrays:\n");
// 	while (i < n)
// 	{
// 		printf("%d ", arr[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	free(arr);
// 	return (0);
// }
