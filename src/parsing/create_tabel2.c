/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tabel2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:50:18 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 11:56:09 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_cmd(void)
{
	t_command	*new_cmd;

	new_cmd = NULL;
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->filename = NULL;
	new_cmd->red_symbol = NULL;
	return (new_cmd);
}

int	is_redirection_tabel(t_token *current_token)
{
	return (current_token->type == TOKEN_REDIR_IN
		|| current_token->type == TOKEN_REDIR_OUT
		|| current_token->type == TOKEN_REDIR_APPEND
		|| current_token->type == TOKEN_REDIR_HERE);
}

void	reset_info(t_info *info)
{
	info->nbr_words = 0;
	info->nbr_reds = 0;
	info->nbr_filenames = 0;
}

void	count_words_redirections(t_list **tokens, t_info *info)
{
	t_list	*tmp;
	t_token	*current_token;

	reset_info(info);
	tmp = *tokens;
	while (tmp)
	{
		current_token = (t_token *)tmp->content;
		if (current_token->type == TOKEN_PIPE)
			break ;
		if (is_redirection_tabel(current_token))
		{
			(info->nbr_reds)++;
			if (tmp->next)
			{
				(info->nbr_filenames)++;
				tmp = tmp->next;
			}
		}
		else
			(info->nbr_words)++;
		tmp = tmp->next;
	}
	*tokens = tmp;
}
