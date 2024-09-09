/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:20:44 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/18 11:50:04 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		in;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		in = 0;
		if (haystack[i] == needle[in])
		{
			while (i < len && haystack[i] == needle[in] && needle[in] != '\0')
			{
				i++;
				in++;
			}
			if (needle[in] == '\0' && i <= len)
				return ((char *)&haystack[i - in]);
			else
				i -= in;
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char haystack[] = "hallo, welt";
// 	char needle[] = ", we";

// 	printf("%s\n", ft_strnstr(haystack, needle, 10));
// 	printf("%s\n", strnstr(haystack, needle, 10));
// }
