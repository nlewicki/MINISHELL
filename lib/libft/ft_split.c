/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:39:51 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/24 11:19:18 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (i == 0 && s[i] != c)
			words++;
		else if (i > 0 && s[i] != c && s[i -1] == c)
			words++;
		i++;
	}
	return (words);
}

static char	*ft_copywords(char const *s, char c)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	word = malloc((i + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (j < i)
	{
		word[j] = s[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static void	ft_free(int j, char **result)
{
	if (result == NULL)
		return ;
	while (j >= 0)
	{
		free(result[j]);
		j--;
	}
	free(result);
}

static void	ft_processwords(char const *s, char c, char **result)
{
	int	j;

	j = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			result[j] = ft_copywords(s, c);
			if (result[j] == NULL)
			{
				ft_free(j, result);
				return ;
			}
			j++;
			while (*s != c && *s != '\0')
				s++;
		}
		else
			s++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**result;

	words = ft_countwords(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (result == NULL)
		return (NULL);
	ft_processwords(s, c, result);
	result[words] = (NULL);
	return (result);
}

// int	main(void)
// {
// 	char const s[] = " ab  c   d e f,g  h";
// 	char c = ' ';

// 	char **result = ft_split(s, c);
// 	if (result != NULL) {
// 		for (int i = 0; result[i] != NULL; i++) {
// 			printf("%s\n", result[i]);
// 			free(result[i]);
// 		}
// 		free(result);
// 	} else {
// 		printf("Memory allocation failed.\n");
// 	}
// 	return (0);
// }
