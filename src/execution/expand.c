/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:37:27 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/14 13:07:57 by mhummel          ###   ########.fr       */
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
	char	*status_str;
	int		i;

	i = 0;
	(*src)++;
	if (**src == '?')
	{
		(*src)++;
		status_str = ft_itoa(*exit_status());
		*length += ft_strlen(status_str);
		return (free(status_str));
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
		*length += ft_strlen(var_value);
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
	char	*status_str;
				char pid_str[16];
	char	*final_result;

	result = malloc(strlen(src) * 2);
	dest = result;
	while (*src)
	{
		if (*src == '$' && !in_single_quotes)
		{
			src++;
			if (*src == '?')
			{
				status_str = ft_itoa(*exit_status());
				ft_strcpy(dest, status_str);
				dest += strlen(status_str);
				free(status_str);
				src++;
			}
			else if (*src == '$')
			{
				snprintf(pid_str, sizeof(pid_str), "%d", getpid());
				ft_strcpy(dest, pid_str);
				dest += strlen(pid_str);
				src++;
			}
			else if (ft_isalpha(*src) || *src == '_')
			{
				i = 0;
				while (ft_isalnum(src[i]) || src[i] == '_')
				{
					var_name[i] = src[i];
					i++;
				}
				var_name[i] = '\0';
				var_value = get_our_env(var_name);
				if (var_value)
				{
					ft_strcpy(dest, var_value);
					dest += strlen(var_value);
				}
				src += i;
			}
			else
				*dest++ = '$';
		}
		else
		{
			if (*src == '\'')
				in_single_quotes = !in_single_quotes;
			*dest++ = *src++;
		}
	}
	*dest = '\0';
	final_result = ft_strdup(result);
	free(result);
	return (final_result);
}
