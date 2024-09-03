/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:20:45 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/03 09:57:05 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int sig)
{
    (void)sig;
    if (g_signal == 0)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        *exit_status() = 1;
    }
}

void handle_signals(void)
{
    if (g_signal == 0)
        signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

int *exit_status(void)
{
    static int status = 0;

    return (&status);
}
