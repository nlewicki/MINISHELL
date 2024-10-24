/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:19:19 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/24 14:33:07 by mhummel          ###   ########.fr       */
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

int	update_existing_var(char **envp, int i, const char *name, char *value)
{
	char	*new_var;

	new_var = create_new_var(NULL, name, value);
	if (!new_var)
		return (1);
	free(envp[i]);
	envp[i] = new_var;
	return (0);
}
