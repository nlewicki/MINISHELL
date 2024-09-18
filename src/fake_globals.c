/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_globals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:09:25 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/18 11:21:49 by nlewicki         ###   ########.fr       */
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
int	*our_shlvl(void)
{
	static int lvl = 0;
	lvl++;
	return (&lvl);
}
