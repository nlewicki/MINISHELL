/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:32:30 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/28 16:12:05 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int signum)
{
	(void)signum;
	rl_done = 1;
	g_interrupt = 1;
	rl_replace_line("", 0);
	close(STDIN_FILENO);
	*exit_status() = 130;
}

void	ft_sigmode_heredoc(void)
{
	set_sighandler(SIGINT, heredoc_handler);
	set_sighandler(SIGQUIT, SIG_IGN);
}
