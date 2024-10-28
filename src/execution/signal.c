/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:20:45 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/28 14:59:19 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	*exit_status() = 1;
}

void	set_sighandler(int signum, void (*handler)(int))
{
	struct sigaction		sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	ft_sigmode_shell(void)
{
	g_interrupt = 0;
	set_sighandler(SIGINT, sigint_handler);
	set_sighandler(SIGQUIT, SIG_IGN);
}

void	handle_signals(void)
{
	rl_catch_signals = 0;
	ft_sigmode_shell();
}
