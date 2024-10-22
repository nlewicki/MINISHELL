/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:31:20 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 13:02:01 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_str_array(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_tabel(void *content)
{
	t_command	*cmd;

	cmd = (t_command *)content;
	if (!cmd)
		return ;
	free_str_array(cmd->args);
	free_str_array(cmd->filename);
	free_str_array(cmd->red_symbol);
	free(cmd);
}
