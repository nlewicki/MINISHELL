/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:49:24 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/12 10:40:07 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_sorted_env(void)
{
	char	**envp;
	char	**sorted_envp;
	char	*eq;
	int		i;
	int		count;

	envp = *env_vars();
	if (!envp)
	{
		write(2, "env: environment not set\n", 25);
		return (1);
	}
	count = count_env_vars(envp);
	sorted_envp = copy_env(envp, count);
	if (!sorted_envp)
		return (1);
	bubble_sort_env(sorted_envp, count);
	i = 0;
	while (i < count)
	{
		eq = ft_strchr(sorted_envp[i], '=');
		if (eq)
			printf("declare -x %.*s=\"%s\"\n", (int)(eq - sorted_envp[i]),
				sorted_envp[i], eq + 1);
		else
			printf("declare -x %s\n", sorted_envp[i]);
		i++;
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
			&& (envp[i][ft_strlen(name)] == '=' || envp[i][ft_strlen(name)] == '\0'))
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
		if (!is_valid_identifier(name))
		{
			fprintf(stderr, "export: '%s': not a valid identifier\n", name);
			free(name);
			return (1);
		}
		if (add_or_update_env(name, equals_sign + 1) != 0)
		{
			fprintf(stderr, "export: failed to set variable '%s'\n", name);
			free(name);
			return (1);
		}
		free(name);
	}
	else
	{
		if (!is_valid_identifier(arg))
		{
			fprintf(stderr, "export: '%s': not a valid identifier\n", arg);
			return (1);
		}
		if (mark_for_export(arg) != 0)
		{
			fprintf(stderr, "export: failed to mark variable '%s' for export\n", arg);
			return (1);
		}
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

int	add_new_env_var(const char *name, char *value, int i)
{
	char	*new_var;
	size_t	len;
	char	**envp;
	char	**new_envp;

	envp = *env_vars();
	new_envp = realloc(envp, (i + 2) * sizeof(char *));
	if (!new_envp)
		return (1);
	if (value && *value)
	{
		len = ft_strlen(name) + ft_strlen(value) + 2;
		new_var = malloc(len);
		if (!new_var)
			return (1);
		snprintf(new_var, len, "%s=%s", name, value);
	}
	else
	{
		len = ft_strlen(name) + 1;
		new_var = malloc(len);
		if (!new_var)
			return (1);
		snprintf(new_var, len, "%s", name);
	}
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	*env_vars() = new_envp;
	return (0);
}

int	add_or_update_env(char *name, char *value)
{
	char	**envp;
	int		i;
	char	*new_var;
	size_t	len;

	envp = *env_vars();
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
		{
			len = ft_strlen(name) + ft_strlen(value) + 2;
			new_var = malloc(len);
			if (!new_var)
				return (1);
			new_var[0] = '\0';
			ft_strlcat(new_var, name, len);
			ft_strlcat(new_var, "=", len);
			ft_strlcat(new_var, value, len);
			return (free(envp[i]), envp[i] = new_var, 0);
		}
		i++;
	}
	return (add_new_env_var(name, value, i));
}
