/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tabel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:36:38 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/09 14:04:27 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_tabelinfo
{
	t_list		*current_token;
	t_list		*new_node;
	t_list		*start_token;
	t_command	*new_cmd;
	size_t		lines_remaining;
	size_t		index;
	size_t		nbr_words;
	size_t		nbr_reds;
	size_t		nbr_filenames;
}				t_tabelinfo;

size_t	count_lines_table(t_list *token_list)
{
	t_list	*tmp;
	size_t	lines;
	t_token	*current_token;

	tmp = token_list;
	lines = 0;
	while (tmp != NULL)
	{
		current_token = (t_token *)tmp->content;
		if (current_token->type == TOKEN_PIPE)
			lines++;
		tmp = tmp->next;
	}
	return (lines + 1);
}

t_command	*create_cmd_block(void)
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

t_list	*create_table(t_list *tokens, t_list *table)
{
	t_tabelinfo	info;

	info.nbr_words = 0;
	info.nbr_reds = 0;
	info.nbr_filenames = 0;
	info.current_token = tokens;
	info.lines_remaining = count_lines_table(tokens);
	info.index = 0;
	while (info.lines_remaining > 0 && info.current_token != NULL)
	{
		printf("Processing line [%zu]\n", index);
		info.new_cmd = create_cmd_block();
		info.new_node = ft_lstnew((void *)info.new_cmd);
		info.start_token = info.current_token;
		nbr_words_redirections(&info);
		printf("Words: %zu, Redirections: %zu, Filenames: %zu\n",
			info.nbr_words, info.nbr_reds, info.nbr_filenames);
		info.new_cmd = allocate_cmd(info);
		ft_lstadd_back(&table, info.new_node);
		info.nbr_words = 0;
		info.nbr_reds = 0;
		info.nbr_filenames = 0;
		info.lines_remaining--;
		info.index++;
	}
	return (table);
}
