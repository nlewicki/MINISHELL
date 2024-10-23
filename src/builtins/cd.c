/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:31:51 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/23 14:01:18 by nlewicki         ###   ########.fr       */
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

	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "~") == 0))
	{
		home = get_home_dir();
		if (!home)
			return (write(2, "cd: HOME not set\n", 17), 1);
		path = home;
	}
	else if (argc > 2)
		return (write(2, "cd: too many arguments\n", 24), 1);
	else
		path = argv[1];
	if (!path)
		return (write(2, "cd: expansion failed\n", 21), 1);
	if (chdir(path) != 0)
	{
		return (*exit_status() = 1, perror("cd"), 1);
	}
	return (0);
}
