/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:08:44 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/28 14:51:25 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_result_len(char *result)
{
	size_t	len;

	len = 0;
	if (result != NULL)
		len = ft_strlen(result);
	return (len);
}

char	*copy_until_dollar(char **result, char *start, char *end)
{
	size_t	len;
	char	*new_result;
	size_t	copy_len;

	len = get_result_len(*result);
	copy_len = end - start;
	new_result = ft_realloc(*result, len + 1, len + copy_len + 1);
	if (new_result == NULL)
		return (NULL);
	*result = new_result;
	if (len == 0)
		(*result)[0] = '\0';
	ft_strlcat(*result, start, len + copy_len + 1);
	return (*result);
}

char	*get_var_name(char **end)
{
	char	*var_name;

	var_name = *end;
	while (ft_isalnum(**end) || **end == '_')
		(*end)++;
	return (var_name);
}

char	*append_var_value(char **result, char *var_value)
{
	size_t	len;
	char	*new_result;

	if (var_value == NULL)
		return (*result);
	len = get_result_len(*result);
	new_result = ft_realloc(*result, len + 1, len + ft_strlen(var_value) + 1);
	if (new_result == NULL)
		return (NULL);
	*result = new_result;
	ft_strlcat(*result, var_value, len + ft_strlen(var_value) + 1);
	return (*result);
}

char	*handle_dollar(char **result, char **start, char **end)
{
	char	*var_name;
	char	*var_value;
	char	tmp;

	(*end)++;
	if (**end == '?')
	{
		var_value = ft_itoa(*exit_status());
		if (append_var_value(result, var_value) == NULL)
			return (free(var_value), NULL);
		free(var_value);
		(*end)++;
	}
	else
	{
		var_name = get_var_name(end);
		tmp = **end;
		**end = '\0';
		var_value = get_our_env(var_name);
		**end = tmp;
		if (append_var_value(result, var_value) == NULL)
			return (NULL);
	}
	*start = *end;
	return (*result);
}
