/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:35:52 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/18 13:29:07 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	uppercase(unsigned int index, char c)
// {
// 	if (c >= 'a' && c <= 'z')
// 		return (c + 32);
// 	return (c);
// }

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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		ind;
	char	*newstr;

	if (s == NULL || f == NULL)
		return (NULL);
	ind = ft_strlen_const(s);
	newstr = malloc((ind + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ind = 0;
	while (s[ind] != '\0')
	{
		newstr[ind] = f(ind, s[ind]);
		ind++;
	}
	newstr[ind] = '\0';
	return (newstr);
}

// int	main(void)
// {
// 	char str[] = "Hello, world!";
// 	char *result;

// 	result = ft_strmapi(str, &uppercase);
// 	if (result)
// 	{
// 		printf("Original string: %s\n", str);
// 		printf("Modified string: %s\n", result);
// 		free(result);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}
// 	return (0);
// }
