/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:37:27 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/16 13:39:57 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper function to get the value of a variable from our env
char *get_our_env(char *var_name)
{
	char	**envp;
	int		i;
	size_t	var_name_len;

	envp = *env_vars();
	i = 0;
	var_name_len = ft_strlen(var_name);
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		char *equals_sign = ft_strchr(envp[i], '=');
		if (equals_sign)
		{
			size_t name_len = equals_sign - envp[i];
			if (name_len == var_name_len && ft_strncmp(envp[i], var_name, var_name_len) == 0)
				return equals_sign + 1;
		}
		i++;
	}
	return (NULL);
}

char	*expand_env_variables(char *src, int in_single_quotes)
{
	char	*result;
	char	*dest;
	char	var_name[256] = {0};
	int		i;
	char	*var_value;

	result = malloc(ft_strlen(src) * 10);
	dest = result;
	while (*src)
	{
		if (*src == '$' && !in_single_quotes)
		{
			src++;
			i = 0;
			if (*src == '?')
			{
				src++;
				ft_strcpy(dest, ft_itoa(*exit_status()));
				dest += ft_strlen(ft_itoa(*exit_status()));
				continue ;
			}
			while (*src && ((*src >= 'A' && *src <= 'Z') || (*src >= 'a'
						&& *src <= 'z') || *src == '_'))
				var_name[i++] = *src++;
			var_value = get_our_env(var_name);
			if (var_value)
			{
				ft_strcpy(dest, var_value);
				dest += ft_strlen(var_value);
			}
			else
			{
				*dest++ = '$';
				ft_strcpy(dest, var_name);
				dest += i;
			}
		}
		else
			*dest++ = *src++;
	}
	*dest = '\0';
	return (result);
}
