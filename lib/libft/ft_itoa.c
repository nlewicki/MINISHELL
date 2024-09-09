/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:01:35 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/18 09:48:13 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	if (n == 0)
		return (0);
	return (1 + count_digits(n / 10));
}

static void	fill_str(char *str, int n, int index)
{
	if (n == 0)
		return ;
	fill_str(str, n / 10, index - 1);
	if (n % 10 < 0)
		str[index] = -(n % 10) + '0';
	else
		str[index] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		num_digits;

	if (n == 0)
		return (ft_strdup("0"));
	num_digits = count_digits(n);
	if (n < 0)
		num_digits++;
	str = malloc((num_digits + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	fill_str(str, n, num_digits - 1);
	str[num_digits] = '\0';
	return (str);
}

// int	main(void)
// {
// 	int number = -2147483648;

// 	printf("Number: %s", ft_itoa(number));
// 	free(ft_itoa(number));
// 	return (0);
// }
