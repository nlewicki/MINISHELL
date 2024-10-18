/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:37:27 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/18 10:09:18 by nlewicki         ###   ########.fr       */
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

void	remove_empty_arg(t_command *row, size_t *i)
{
	size_t	j;

	free(row->args[*i]);
	j = *i;
	while (row->args[j])
	{
		row->args[j] = row->args[j + 1];
		j++;
	}
	(*i)--;
}

static void	process_arg(t_command *row, size_t *i)
{
	char	*expanded;

	expanded = expand_env_variables(row->args[*i]);
	if (expanded)
	{
		if (*expanded == '\0')
		{
			free(expanded);
			remove_empty_arg(row, i);
		}
		else
		{
			free(row->args[*i]);
			row->args[*i] = expanded;
		}
	}
}

void	handle_expansion(t_list *tabel)
{
	t_list		*tmp;
	t_command	*row;
	size_t		i;

	tmp = tabel;
	while (tmp)
	{
		row = tmp->content;
		i = 0;
		while (row->args[i])
		{
			if (ft_strchr(row->args[i], '$') != NULL)
				process_arg(row, &i);
			i++;
		}
		tmp = tmp->next;
	}
}

t_list	*expansion(t_list *tabel)
{
	handle_expansion(tabel); // needs rework
	remove_quotes(tabel); // seems to be working
	print_tabel(tabel);
	return (NULL);
}
