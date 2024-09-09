/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:25:29 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/12 12:17:57 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

// int	main(void)
// {
// 	int	c;
// 	int	d;

// 	d = 'a';
// 	c = 'a';
// 	c = toupper(c);
// 	printf ("%c\n", c);
// 	d = ft_toupper(d);
// 	printf ("%c\n", d);
// }
