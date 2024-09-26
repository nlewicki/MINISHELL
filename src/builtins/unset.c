/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:37 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/26 11:09:45 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_variable_name(const char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	while (*++name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
	}
	return (1);
}

static void	remove_env_var(const char *name)
{
	char	**env;
	int		i;
	size_t	name_len;

	env = *env_vars();
	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && (env[i][name_len] == '='
			|| env[i][name_len] == '\0'))
		{
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

int	ft_unset(char *argv[], int argc)
{
	int	i;
	int	status;

	status = 0;
	if (argc < 2)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (is_valid_variable_name(argv[i]))
			remove_env_var(argv[i]);
		else
		{
			write(2, "unset: '", 8);
			write(2, argv[i], strlen(argv[i]));
			write(2, "': not a valid identifier\n", 27);
			status = 1;
		}
		i++;
	}
	return (status);
}
