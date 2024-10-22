/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolewicki <nicolewicki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:38:54 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/22 14:12:27 by nicolewicki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shell_history(void)
{
	// rl_clear_history();
}

void	handle_history(char *input)
{
	if (g_signal == 0)
	{
		if (ft_strlen(input) > 0)
			add_history(input);
		else
			free(input);
	}
}
