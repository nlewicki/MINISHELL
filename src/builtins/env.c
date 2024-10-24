/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:01:10 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/24 13:03:28 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(void)
{
	char	**envp;
	int		i;
	char	*equals_sign;

	envp = *env_vars();
	i = 0;
	if (!envp)
	{
		write(2, "env: environment not set\n", 25);
		return (1);
	}
	while (envp[i])
	{
		equals_sign = ft_strchr(envp[i], '=');
		if (equals_sign)
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

char	**copy_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i--)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	return (new_envp[i] = NULL, new_envp);
}

void	free_env(char **my_envp)
{
	size_t	i;

	i = 0;
	while (my_envp[i])
	{
		free(my_envp[i]);
		i++;
	}
	free(my_envp);
}
