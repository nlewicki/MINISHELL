/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:36:37 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/03 13:26:27 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_variable_name(const char *name)
{
	if (!isalpha(*name) && *name != '_')
		return (0);
	while (*++name)
	{
		if (!isalnum(*name) && *name != '_')
			return (0);
	}
	return (1);
}

static void remove_env_var(const char *name)
{
	char **env = *env_vars();
	int i = 0;
	size_t name_len = strlen(name);

	while (env[i])
	{
		if (strncmp(env[i], name, name_len) == 0 &&
			(env[i][name_len] == '=' || env[i][name_len] == '\0'))
		{
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			return;
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
	{
		fprintf(stderr, "unset: not enough arguments\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (is_valid_variable_name(argv[i]))
		{
			remove_env_var(argv[i]);
		}
		else
		{
			fprintf(stderr, "unset: '%s': not a valid identifier\n", argv[i]);
			status = 1;
		}
		i++;
	}
	return (status);
}
