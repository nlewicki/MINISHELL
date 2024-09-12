/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:01:10 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/12 10:33:46 by nlewicki         ###   ########.fr       */
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
		if (equals_sign && *(equals_sign + 1) != '\0')
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

void	set_env_vars(char **envp)
{
	char	***env;
	size_t	i;
	size_t	j;

	env = env_vars();
	i = 0;
	while (envp[i])
		i++;
	*env = malloc((i + 1) * sizeof(char *));
	if (!*env)
	{
		perror("malloc");
		exit(1);
	}
	j = -1;
	while (++j < i)
	{
		(*env)[j] = ft_strdup(envp[j]);
		if (!(*env)[j])
		{
			perror("strdup");
			exit(1);
		}
	}
	(*env)[i] = NULL;
}
