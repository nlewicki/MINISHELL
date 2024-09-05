/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_globals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:09:25 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/05 09:06:50 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*exit_status(void)
{
	static int	status = 0;

	return (&status);
}

char	***env_vars(void)
{
	static char	**env = NULL;

	return (&env);
}
