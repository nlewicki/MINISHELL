/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:31:51 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/27 09:37:49 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_dir(void)
{
	char	**env;
	int		i;

	env = *env_vars();
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

int	ft_cd(char *argv[], int argc)
{
	char	*path;
	char	*home;
	char	*expanded_path;

	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "~") == 0))
	{
		home = get_home_dir();
		if (!home)
			return (write(2, "cd: HOME not set\n", 17), 1);
		path = home;
	}
	else if (argc > 2)
		return (0);
	else
		path = argv[1];
	expanded_path = expand_env_variables(path, 0);
	if (!expanded_path)
		return (write(2, "cd: expansion failed\n", 21), 1);
	if (chdir(path) != 0)
	{
		free(expanded_path);
		return (perror("cd"), 1);
	}
	free(expanded_path);
	return (0);
}
