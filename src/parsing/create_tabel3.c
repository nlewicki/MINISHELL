/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tabel3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:50:55 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 11:56:14 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*allocate_cmd(t_command *new_cmd, t_list *token_position,
		t_info *info)
{
	new_cmd->args = malloc(sizeof(char *) * (info->nbr_words + 1));
	if (!new_cmd->args)
		return (NULL);
	new_cmd->filename = malloc(sizeof(char *) * (info->nbr_filenames + 1));
	if (!new_cmd->filename)
	{
		free(new_cmd->args);
		return (NULL);
	}
	new_cmd->red_symbol = malloc(sizeof(char *) * (info->nbr_reds + 1));
	if (!new_cmd->red_symbol)
	{
		free(new_cmd->args);
		free(new_cmd->filename);
		return (NULL);
	}
	new_cmd = fill_cmd(new_cmd, token_position);
	return (new_cmd);
}

void	process_redirection(t_command *cmd, t_list **tmp, size_t *j)
{
	t_token	*next_token;

	cmd->red_symbol[*j] = ft_strdup(((t_token *)(*tmp)->content)->content);
	if ((*tmp)->next)
	{
		*tmp = (*tmp)->next;
		next_token = (t_token *)(*tmp)->content;
		cmd->filename[*j] = ft_strdup(next_token->content);
	}
	(*j)++;
}

void	process_argument(t_command *cmd, t_token *current_token, size_t *i)
{
	cmd->args[*i] = ft_strdup(current_token->content);
	(*i)++;
}

t_command	*fill_cmd(t_command *cmd, t_list *position)
{
	t_list	*tmp;
	t_token	*current_token;
	size_t	i;
	size_t	j;

	tmp = position;
	i = 0;
	j = 0;
	while (tmp)
	{
		current_token = (t_token *)tmp->content;
		if (current_token->type == TOKEN_PIPE)
			break ;
		if (is_redirection_tabel(current_token))
			process_redirection(cmd, &tmp, &j);
		else
			process_argument(cmd, current_token, &i);
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
	cmd->filename[j] = NULL;
	cmd->red_symbol[j] = NULL;
	return (cmd);
}
