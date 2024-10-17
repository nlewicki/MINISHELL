/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:37:27 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/17 11:05:44 by nlewicki         ###   ########.fr       */
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

char	*expand_env_variables(char *src)
{
	(void)src;
	return (NULL);
}

void	check_dollar(t_list *tabel)
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
			printf("row->args[%zu]: %s\n", i, row->args[i]);
			if (row->args[i][0] == '$')
			{
				row->args[i] = expand_env_variables(row->args[i]);
			}
			i++;
		}
		tmp = tmp->next;
	}
}

t_list	*expansion(t_list *tabel)
{
	// check_quotes(tabel);
	check_dollar(tabel);
	return (NULL);
}
