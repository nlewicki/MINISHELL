/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:47:23 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/24 14:29:57 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_expanded_filename(t_command *cmd, size_t *i, char *expanded,
		char *temp)
{
	if (*expanded == '\0')
	{
		free(expanded);
		if (cmd->filename[*i + 1] != NULL)
			remove_empty_arg(cmd, i);
		else
		{
			*is_expanded() = 1;
			free(cmd->filename[*i]);
			cmd->filename[*i] = ft_strdup("");
		}
	}
	if (ft_strchr(expanded, ' ') != NULL)
	{
		ft_putstr_fd(temp, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		free(expanded);
		*exit_status() = 1;
	}
	else
	{
		free(cmd->filename[*i]);
		cmd->filename[*i] = expanded;
	}
}

void	process_filename(t_command *cmd, size_t *i)
{
	char	*temp;
	char	*expanded;

	temp = ft_strdup(cmd->filename[*i]);
	if (temp == NULL)
		return ;
	expanded = expand_env_variables(temp);
	free(temp);
	if (expanded != NULL)
		handle_expanded_filename(cmd, i, expanded, temp);
}
