/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:26:58 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/18 13:25:39 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_const(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		ind;
	char	*strjoin;

	i = ft_strlen_const(s1);
	ind = ft_strlen_const(s2);
	strjoin = malloc ((ind + i + 1) * sizeof(char));
	if (strjoin == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	ind = 0;
	while (s2[ind] != '\0')
	{
		strjoin[i + ind] = s2[ind];
		ind++;
	}
	strjoin[i + ind] = '\0';
	return (strjoin);
}

// int	main(void)
// {
// 	char	str[] = "hallo";
// 	char	str2[] = " welt";

// 	printf ("%s\n", ft_strjoin(str, str2));
// 	return (0);
// }
