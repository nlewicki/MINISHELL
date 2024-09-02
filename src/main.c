/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:41 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/02 10:26:02 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

int	parse_command(char *input, char *args[])
{
	char *token;
	int arg_count = 0;

	// Split the input string into tokens
	token = strtok(input, " ");
	while (token != NULL && arg_count < MAX_ARGS) {
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}

	return arg_count;
}

int main()
{
	char input[MAX_COMMAND_LENGTH];
	char *args[MAX_ARGS];
	int arg_count;
	int i;

	while (1)
	{
		printf("minishell> ");
		fgets(input, MAX_COMMAND_LENGTH, stdin);

		// Remove the newline character from the end of the input
		input[strcspn(input, "\n")] = '\0';

		arg_count = parse_command(input, args);

		printf("\nCommand: %s\n", args[0]);
		printf("\nArguments:\n");
		i = 1;
		while (i < arg_count)
		{
			printf("• %s\n", args[i]);
			i++;
		}
		printf("\n");
	}
	return 0;
}
