/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:57 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/03 10:28:37 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int argc)
{
	char	*cwd;

	if (argc > 1)
	{
		write(2, "pwd: too many arguments\n", 24);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		write(2, "pwd: error retrieving current directory\n", 40);
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
