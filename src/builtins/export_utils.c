/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:19 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/09 11:21:34 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_env(const void *a, const void *b)
{
	char	*env_a;
	char	*env_b;

	env_a = *(char **)a;
	env_b = *(char **)b;
	return (ft_strcmp(env_a, env_b));
}

void	bubble_sort_env(char **envp, int count)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < (count - 1 - i))
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**copy_env(char **envp, int count)
{
	char	**copy;
	int		i;

	copy = malloc((count + 1) * sizeof(char *));
	i = 0;
	if (!copy)
	{
		perror("malloc");
		return (NULL);
	}
	while (i < count)
	{
		copy[i] = envp[i];
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

int	is_valid_identifier(const char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
	}
	return (1);
}
