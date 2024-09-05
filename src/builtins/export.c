/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:49:24 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/05 10:41:50 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s) + 1;
	new = malloc(len);
	if (new == NULL)
		return (NULL);
	return (ft_memcpy(new, s, len));
}

int	compare_env(const void *a, const void *b)
{
	char	*env_a;
	char	*env_b;

	env_a = *(char **)a;
	env_b = *(char **)b;
	return (ft_strcmp(env_a, env_b));
}

void	bubble_sort_env(char **envp, int count)
{
	char	*temp;

	int i, j;
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
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

int	print_sorted_env(void)
{
	char	**envp;
	char	**sorted_envp;
	char	*eq;

	int i, count;
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
	free(sorted_envp);
	return (0);
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
		{
			fprintf(stderr, "export: memory allocation error\n");
			return (1);
		}
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
	else if (!is_valid_identifier(arg))
	{
		fprintf(stderr, "export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	else if (add_or_update_env(arg, "") != 0)
	{
		fprintf(stderr, "export: failed to set variable '%s'\n", arg);
		return (1);
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

int	add_new_env_var(char *name, char *value, int i)
{
	char	*new_var;
	size_t	len;
	char	**envp;
	char	**new_envp;

	len = ft_strlen(name) + strlen(value) + 2;
	envp = *env_vars();
	new_envp = realloc(envp, (i + 2) * sizeof(char *));
	if (!new_envp)
		return (1);
	new_var = malloc(len);
	if (!new_var)
		return (1);
	snprintf(new_var, len, "%s=%s", name, value);
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
			strlcat(new_var, name, len);
			strlcat(new_var, "=", len);
			strlcat(new_var, value, len);
			free(envp[i]);
			envp[i] = new_var;
			return (0);
		}
		i++;
	}
	return (add_new_env_var(name, value, i));
}
