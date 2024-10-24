/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:31:51 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/24 09:27:52 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(const char *var_name)
{
	char	**env;
	int		i;
	size_t	len;

	env = *env_vars();
	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	update_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	old_pwd = get_env_var("PWD");
	if (old_pwd && add_or_update_env("OLDPWD", old_pwd) != 0)
		return (ft_putendl_fd("cd: failed to update OLDPWD", 2), 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (add_or_update_env("PWD", cwd) != 0)
			return (ft_putendl_fd("cd: failed to update PWD", 2), 1);
	}
	else
		return (perror("cd: getcwd"), 1);
	return (0);
}

static char	*get_cd_path(char *argv[], int argc)
{
	char	*path;
	char	*home;

	if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], "~") == 0))
	{
		home = get_env_var("HOME");
		if (!home)
			return (ft_putendl_fd("cd: HOME not set", 2), NULL);
		path = home;
	}
	else if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
	{
		path = get_env_var("OLDPWD");
		if (!path)
			return (ft_putendl_fd("cd: OLDPWD not set", 2), NULL);
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		path = argv[1];
	return (path);
}

int	ft_cd(char *argv[], int argc)
{
	char	*path;

	if (argc > 2)
		return (0);
	path = get_cd_path(argv, argc);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		*exit_status() = 1;
		perror("cd");
		return (1);
	}
	if (update_pwd() != 0)
		return (1);
	return (0);
}
