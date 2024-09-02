/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:45:57 by mhummel           #+#    #+#             */
/*   Updated: 2024/09/02 12:21:15 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int argc)
{
	char	*cwd;
	size_t	size;

	if (argc > 1)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	size = 1024;
	while (1)
	{
		cwd = malloc(size);
		if (cwd == NULL)
		{
			perror("malloc");
			return (1);
		}
		if (getcwd(cwd, size) != NULL)
		{
			printf("%s\n", cwd);
			free(cwd);
			return (0);
		}
		free(cwd);
		if (errno != ERANGE)
		{
			perror("getcwd");
			return (1);
		}
		size *= 2; // Double the buffer size and try again
	}
}
