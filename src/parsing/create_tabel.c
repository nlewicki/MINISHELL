/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tabel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:45:16 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 11:54:01 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*init_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->nbr_words = 0;
	info->nbr_reds = 0;
	info->nbr_filenames = 0;
	info->blocks = 0;
	info->table = NULL;
	info->tmp = NULL;
	info->tmp2 = NULL;
	return (info);
}

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

void	process_command(t_info *info)
{
	t_command	*new_cmd;
	t_list		*new_node;

	new_cmd = init_cmd();
	if (new_cmd == NULL)
		return ;
	new_node = ft_lstnew((void *)new_cmd);
	info->tmp2 = info->tmp;
	count_words_redirections(&info->tmp, info);
	new_cmd = allocate_cmd(new_cmd, info->tmp2, info);
	ft_lstadd_back(&info->table, new_node);
}

t_list	*free_info_return_table(t_info *info)
{
	t_list	*table;

	table = info->table;
	free(info);
	return (table);
}

t_list	*create_tabel(t_list *tokens)
{
	t_info	*info;

	info = init_info();
	if (info == NULL)
		return (NULL);
	info->blocks = count_lines(tokens);
	info->tmp = tokens;
	while (info->blocks > 0 && info->tmp != NULL)
	{
		process_command(info);
		if (info->tmp == NULL)
		{
			info->blocks--;
			break ;
		}
		info->tmp = info->tmp->next;
		info->blocks--;
	}
	return (free_info_return_table(info));
}
