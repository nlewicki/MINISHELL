/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:03:05 by nlewicki          #+#    #+#             */
/*   Updated: 2024/03/18 13:28:55 by nlewicki         ###   ########.fr       */
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

static char	*ft_mallocspace(int len, char *s1, int start)
{
	int		i;
	char	*newstr;

	i = 0;
	if (len <= 0)
	{
		newstr = malloc(1 * sizeof(char));
		if (newstr == NULL)
			return (NULL);
	}
	else
	{
		newstr = malloc((len + 1) * sizeof(char));
		if (newstr == NULL)
			return (NULL);
		while (i < len)
		{
			newstr[i] = s1[start + i];
			i++;
		}
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	int		len;

	start = 0;
	end = ft_strlen_const(s1) - 1;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	len = end - start + 1;
	return (ft_mallocspace(len, (char *)s1, start));
}

// int	main(void)
// {
// 	char	s[] = "  		Hallo  		";
// 	char	set[] = "	 ";

// 	printf("%s\n", ft_strtrim(s, set));
// 	free (ft_strtrim(s, set));
// 	return (0);
// }
