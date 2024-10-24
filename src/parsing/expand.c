/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:37:27 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/24 12:47:12 by nlewicki         ###   ########.fr       */
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
			return (envp[i] + ft_strlen(name) + 1);
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

void	handle_expansion(t_command *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '$') != NULL)
			process_arg(cmd, &i);
		i++;
	}
	i = 0;
	while (cmd->filename[i])
	{
		if (ft_strchr(cmd->filename[i], '$') != NULL)
			process_filename(cmd, &i);
		i++;
	}
}

t_list	*expansion(t_list *tabel)
{
	t_list		*tmp;
	t_command	*cmd;

	tmp = tabel;
	while (tmp)
	{
		cmd = tmp->content;
		handle_expansion(cmd);
		remove_quotes(cmd);
		tmp = tmp->next;
	}
	return (tabel);
}
