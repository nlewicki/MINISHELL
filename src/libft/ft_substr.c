/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:13:33 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/18 13:33:54 by nlewicki         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	slen;
	unsigned int	ind;

	slen = ft_strlen_const(s);
	if (start >= slen)
	{
		substr = (char *)malloc(1);
		if (substr)
			substr[0] = '\0';
		return (substr);
	}
	if (len > slen - start)
		len = slen - start;
	substr = malloc ((len + 1) * sizeof(char));
	ind = 0;
	if (substr == NULL)
		return (NULL);
	while (ind < len && s[start + ind] != '\0')
	{
		substr[ind] = s[start + ind];
		ind++;
	}
	substr[ind] = '\0';
	return (substr);
}

// int	main(void)
// {
// 	char	str[] = "halloiadsa";
// 	int		start = 15;
// 	size_t	len = 5;

// 	printf ("%s\n", ft_substr(str, start, len));
// 	return (0);
// }
