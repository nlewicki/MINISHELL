/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:38:54 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/02 12:49:37 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(const char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}

void	clear_shell_history(void)
{
	rl_clear_history();
}
