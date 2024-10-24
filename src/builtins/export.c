/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:49:24 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/24 14:40:09 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	print_sorted_env(void)
{
	char	**envp;
	char	**sorted_envp;
	char	*eq;
	int		i;
	int		count;

	envp = *env_vars();
	if (!envp)
		return (ft_err("env: environment not set\n", NULL, NULL), 1);
	count = count_env_vars(envp);
	sorted_envp = copy_env(envp, count);
	if (!sorted_envp)
		return (1);
	bubble_sort_env(sorted_envp, count);
	i = -1;
	while (++i < count)
	{
		eq = ft_strchr(sorted_envp[i], '=');
		if (eq)
			printf("declare -x %.*s=\"%s\"\n", (int)(eq - sorted_envp[i]),
				sorted_envp[i], eq + 1);
		else
			printf("declare -x %s\n", sorted_envp[i]);
	}
	return (free(sorted_envp), 0);
}

int	mark_for_export(const char *name)
{
	char	**envp;
	int		i;

	i = 0;
	envp = *env_vars();
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& (envp[i][ft_strlen(name)] == '='
			|| envp[i][ft_strlen(name)] == '\0'))
			return (0);
		i++;
	}
	return (add_new_env_var(name, NULL, i));
}

int	ft_export_args(char *arg)
{
	char	*name;
	char	*equals_sign;

	equals_sign = ft_strchr(arg, '=');
	if (equals_sign)
	{
		name = ft_strdup(arg);
		if (!name)
			return (1);
		equals_sign = ft_strchr(name, '=');
		*equals_sign = '\0';
		if (set_export_error(name, equals_sign + 1) != 0)
			return (1);
	}
	else
	{
		if (!is_valid_identifier(arg))
			return (*exit_status() = 1, ft_err("export: ", arg,
					": not a valid identifier\n"), 1);
		if (add_or_update_env(arg, NULL) != 0)
			return (ft_err("export: failed to mark variable ", arg,
					" for export\n"), 1);
	}
	return (0);
}

int	ft_export(char **args, int arg_count)
{
	int	i;

	i = 1;
	if (arg_count == 1)
		return (print_sorted_env());
	while (i < arg_count)
	{
		if (ft_export_args(args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
