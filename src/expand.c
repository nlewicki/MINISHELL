/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:37:27 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/19 12:26:12 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_our_env(const char *name)
{
	char	**envp;
	int		i;

	envp = *env_vars();
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
		{
			return (envp[i] + ft_strlen(name) + 1);
		}
		i++;
	}
	return (NULL);
}

void	handle_expansion(size_t *length, const char **src)
{
	char	var_name[256];
	char	*var_value;
	int		i;

	i = 0;
	(*src)++;
	if (**src == '?')
	{
		(*src)++;
		length += ft_strlen(ft_itoa(*exit_status()));
		return ;
	}
	while (**src && ((**src >= 'A' && **src <= 'Z') || (**src >= 'a'
				&& **src <= 'z') || **src == '_'))
	{
		var_name[i++] = **src;
		(*src)++;
	}
	var_name[i] = '\0';
	var_value = get_our_env(var_name);
	if (var_value)
		length += ft_strlen(var_value);
	else
		length += i + 1;
}

size_t	calculate_expanded_length(const char *src, int in_single_quotes)
{
	size_t	length;

	length = 0;
	while (*src)
	{
		if (*src == '$' && !in_single_quotes)
			handle_expansion(&length, &src);
		else
		{
			length++;
			src++;
		}
	}
	return (length);
}

char	*expand_env_variables(char *src, int in_single_quotes)
{
	char	*result;
	char	*dest;
	char	var_name[256] = {0};
	int		i;
	char	*var_value;

	result = malloc(ft_strlen(src) * calculate_expanded_length(src, in_single_quotes));
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
