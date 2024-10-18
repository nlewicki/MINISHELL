/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tabel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:45:16 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/18 14:38:25 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_lines(t_list *tokens)
{
	t_list	*tmp;
	size_t	lines;

	tmp = tokens;
	lines = 0;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == TOKEN_PIPE)
			lines++;
		tmp = tmp->next;
	}
	return (lines + 1);
}

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

t_info	*init_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->nbr_words = 0;
	info->nbr_reds = 0;
	info->nbr_filenames = 0;
	return (info);
}

void	reset_info(t_info *info)
{
	info->nbr_words = 0;
	info->nbr_reds = 0;
	info->nbr_filenames = 0;
}

int	is_redirection_tabel(t_token *current_token)
{
	return (current_token->type == TOKEN_REDIR_IN
		|| current_token->type == TOKEN_REDIR_OUT
		|| current_token->type == TOKEN_REDIR_APPEND
		|| current_token->type == TOKEN_REDIR_HERE);
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

t_command	*fill_cmd(t_command *cmd, t_list *position)
{
	t_list	*tmp;
	t_token	*next_token;
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
		{
			cmd->red_symbol[j] = ft_strdup(current_token->content);
			if (tmp->next)
			{
				tmp = tmp->next;
				next_token = (t_token *)tmp->content;
				cmd->filename[j] = ft_strdup(next_token->content);
			}
			j++;
		}
		else
		{
			cmd->args[i] = ft_strdup(current_token->content);
			i++;
		}
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
	cmd->filename[j] = NULL;
	cmd->red_symbol[j] = NULL;
	return (cmd);
}

t_command	*allocate_cmd(t_command *new_cmd, t_list *token_position, t_info *info)
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

t_list	*create_tabel(t_list *tokens)
{
	t_list		*table = NULL;
	size_t		blocks;
	t_list		*tmp;
	t_list		*tmp2;
	t_command	*new_cmd;
	t_list		*new_node;
	t_info		*info;

	info = init_info();
	if (!info)
		return (NULL);

	blocks = count_lines(tokens);
	// printf("BLOCKS: %zu\n", blocks);

	tmp = tokens;
	while (blocks > 0 && tmp != NULL)
	{
		new_cmd = init_cmd();
		if (!new_cmd)
			return (NULL);
		new_node = ft_lstnew((void *)new_cmd);
		tmp2 = tmp;
		count_words_redirections(&tmp, info);
		// printf("nbr of words: %zu\n", info->nbr_words);
		// printf("nbr of reds: %zu\n", info->nbr_reds);
		// printf("nbr of filenames: %zu\n", info->nbr_filenames);
		new_cmd = allocate_cmd(new_cmd, tmp2, info);

		ft_lstadd_back(&table, new_node);
		if (tmp == NULL)
		{
			blocks--;
			// printf("[%zu]\n", blocks);
			break ;
		}
		tmp = tmp->next;
		blocks--;
		// printf("[%zu]\n", blocks);
	}
	return (table);
}
