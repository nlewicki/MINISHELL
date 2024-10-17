/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:37:27 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/17 13:20:33 by nlewicki         ###   ########.fr       */
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

static size_t	get_result_len(char *result)
{
	size_t	len;

	len = 0;
	if (result != NULL)
		len = ft_strlen(result);
	return (len);
}

static char	*copy_until_dollar(char **result, char *start, char *end)
{
	size_t	len;
	char	*new_result;

	len = get_result_len(*result);
	len += end - start;
	new_result = ft_realloc(*result, len + 1);
	if (new_result == NULL)
		return (NULL);
	*result = new_result;
	(*result)[len] = '\0';
	strncat(*result, start, end - start);
	return (*result);
}

static char	*get_var_name(char **end)
{
	char	*var_name;

	var_name = *end;
	while (ft_isalnum(**end) || **end == '_')
		(*end)++;
	return (var_name);
}

static char	*append_var_value(char **result, char *var_value)
{
	size_t	len;
	char	*new_result;

	if (var_value == NULL)
		return (*result);
	len = get_result_len(*result);
	len += ft_strlen(var_value);
	new_result = ft_realloc(*result, len + 1);
	if (new_result == NULL)
		return (NULL);
	*result = new_result;
	strcat(*result, var_value);
	return (*result);
}

static char	*handle_dollar(char **result, char **start, char **end)
{
	char	*var_name;
	char	*var_value;
	char	tmp;

	(*end)++;
	var_name = get_var_name(end);
	tmp = **end;
	**end = '\0';
	var_value = get_our_env(var_name);
	**end = tmp;
	if (append_var_value(result, var_value) == NULL)
		return (NULL);
	*start = *end;
	return (*result);
}

char	*expand_env_variables(char *src)
{
	char	*result;
	char	*start;
	char	*end;

	result = NULL;
	start = src;
	end = src;
	while (*end)
	{
		if (*end == '$' && (ft_isalnum(*(end + 1)) || *(end + 1) == '_'))
		{
			if (copy_until_dollar(&result, start, end) == NULL)
				return (NULL);
			if (handle_dollar(&result, &start, &end) == NULL)
				return (NULL);
		}
		else
			end++;
	}
	if (*start && copy_until_dollar(&result, start, end) == NULL)
		return (NULL);
	if (result == NULL)
		result = ft_strdup(src);
	return (result);
}

void handle_expansion(t_list *tabel)
{
	t_list		*tmp;
	t_command	*row;
	size_t		i;
	char		*expanded;

	tmp = tabel;
	while (tmp)
	{
		row = tmp->content;
		i = 0;
		while (row->args[i])
		{
			printf("row->args[%zu]: %s\n", i, row->args[i]);
			if (ft_strchr(row->args[i], '$') != NULL)
			{
				expanded = expand_env_variables(row->args[i]);
				if (expanded)
				{
					free(row->args[i]);
					row->args[i] = expanded;
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}

t_list	*expansion(t_list *tabel)
{
	handle_expansion(tabel);
	// remove_quotes(tabel);
	print_tabel(tabel);
	return (NULL);
}
