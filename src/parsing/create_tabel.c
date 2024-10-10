/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tabel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:45:16 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/10 12:13:23 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_command
// {
// 	char	**args;
// 	char	**filename;
// 	char	**red_symbol;
// }	t_command;

size_t count_lines(t_list *tokens)
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

// typedef struct s_info
// {
// 	size_t	nbr_words;
// 	size_t	nbr_reds;
// 	size_t	nbr_filenames;
// }	t_info;

// t_info	*init_info(void)
// {
// 	t_info	*info;

// 	info = malloc(sizeof(t_info));
// 	if (!info)
// 		return (NULL);
// 	info->nbr_words = 0;
// 	info->nbr_reds = 0;
// 	info->nbr_filenames = 0;
// 	return (info);
// }

int	is_redirection(t_token *current_token)
{
	if (current_token->type == TOKEN_REDIR_IN
		|| current_token->type == TOKEN_REDIR_OUT
		|| current_token->type == TOKEN_REDIR_APPEND
		|| current_token->type == TOKEN_REDIR_HERE)
		{
			printf("REDIRECTION\n");
			return (1);
		}
	else
	{
		printf("NOT REDIRECTION\n");
		return (0);
	}
}

void	count_words_redirections(t_list **tokens, size_t *nbr_words, size_t *nbr_reds, size_t *nbr_filenames)
{
	t_list	*tmp;
	t_token	*current_token;
	*nbr_filenames = 0;
	*nbr_reds = 0;
	*nbr_words = 0;

	tmp = *tokens;
	while (tmp)
	{
		current_token = (t_token *)tmp->content;
		if (current_token->type == TOKEN_PIPE)
			break ;
		if (is_redirection(current_token))
		{
			(*nbr_reds)++;
			if (tmp->next)
			{
				(*nbr_filenames)++;
				tmp = tmp->next;
			}
		}
		else
			(*nbr_words)++;
		tmp = tmp->next;
	}
	*tokens = tmp;
}

t_list	*create_tabel(t_list *token_list)
{
	t_list	*table = NULL;
	size_t	blocks;
	t_list	*tmp;
	t_command	*new_cmd;
	t_list	*new_node;
	size_t	nbr_words = 0;
	size_t	nbr_reds= 0;
	size_t	nbr_filenames = 0;


	blocks = count_lines(token_list);
	printf("BLOCKS: %zu\n", blocks);

	tmp = token_list;
	while (blocks > 0 && tmp != NULL)
	{
		new_cmd = init_cmd();
		new_node = ft_lstnew((void *)new_cmd);

		count_words_redirections(&tmp, &nbr_words, &nbr_reds, &nbr_filenames);
		printf("nbr of words: %zu\n", nbr_words);
		printf("nbr of reds: %zu\n", nbr_reds);
		printf("nbr of filenames: %zu\n", nbr_filenames);

		ft_lstadd_back(&table, new_node);
		if (tmp == NULL)
			break ;
		tmp = tmp->next;
		blocks--;
		printf("[%zu]\n", blocks);
	}
	return (table);
}
