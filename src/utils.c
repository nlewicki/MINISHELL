/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:31:20 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 13:32:40 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_list *tabel)
{
	int	result;
	int	orig_stdin;
	int	orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(tabel))
	{
		restore_std_fds(orig_stdin, orig_stdout);
		return (1);
	}
	if (ft_lstsize(tabel) > 1)
		result = execute_piped_commands(tabel);
	else
		result = execute_command(tabel);
	restore_std_fds(orig_stdin, orig_stdout);
	return (result);
}

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
