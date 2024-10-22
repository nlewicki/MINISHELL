/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:04:22 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 12:04:46 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_and_set_empty(t_command *cmd, size_t *i, char *expanded)
{
	free(expanded);
	if (cmd->args[*i + 1] != NULL)
	{
		remove_empty_arg(cmd, i);
	}
	else
	{
		*is_expanded() = 1;
		free(cmd->args[*i]);
		cmd->args[*i] = ft_strdup("");
	}
}

static void	replace_arg(t_command *cmd, size_t i, char *expanded)
{
	free(cmd->args[i]);
	cmd->args[i] = expanded;
}

static void	handle_expanded_arg(t_command *cmd, size_t *i, char *expanded)
{
	if (*expanded == '\0')
	{
		free_and_set_empty(cmd, i, expanded);
	}
	else
	{
		replace_arg(cmd, *i, expanded);
	}
}

void	process_arg(t_command *cmd, size_t *i)
{
	char	*temp;
	char	*expanded;

	temp = ft_strdup(cmd->args[*i]);
	if (temp == NULL)
	{
		return ;
	}
	expanded = expand_env_variables(temp);
	free(temp);
	if (expanded != NULL)
	{
		handle_expanded_arg(cmd, i, expanded);
	}
}
