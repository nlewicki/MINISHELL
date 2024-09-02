/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:41 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/02 12:11:49 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void	strip_quotes(char *str)
{
	int	len;

	len = strlen(str);
	if (len >= 2)
	{
		if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len
				- 1] == '\''))
		{
			memmove(str, str + 1, len - 2);
			str[len - 2] = '\0';
		}
	}
}

int	parse_command(char *input, char *args[])
{
	int		arg_count;
	char	*token_start;
	int		in_quotes;
	char	quote_char;
	int		i;

	arg_count = 0;
	token_start = input;
	in_quotes = 0;
	quote_char = 0;
	while (*input != '\0' && arg_count < MAX_ARGS)
	{
		if ((*input == '"' || *input == '\'') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = *input;
			token_start = input;
		}
		else if (*input == quote_char && in_quotes)
		{
			in_quotes = 0;
			args[arg_count] = token_start;
			arg_count++;
			token_start = input + 1;
		}
		else if (isspace(*input) && !in_quotes)
		{
			if (token_start != input)
			{
				*input = '\0';
				args[arg_count] = token_start;
				arg_count++;
			}
			token_start = input + 1;
		}
		input++;
	}
	if (token_start != input && arg_count < MAX_ARGS)
	{
		args[arg_count] = token_start;
		arg_count++;
	}
	// Strip quotes from all arguments
	i = 0;
	while (i < arg_count)
	{
		strip_quotes(args[i]);
		i++;
	}
	return (arg_count);
}

int	execute_command(char *args[])
{
	if (strcmp(args[0], "pwd") == 0 || strcmp(args[0], "PWD") == 0)
	{
		return (pwd());
	}
	// Add other built-in commands here
	// If not a built-in command, you can add logic to execute external commands
	printf("Command not found: %s\n", args[0]);
	return (1);
}

int	main(void)
{
	char	input[MAX_COMMAND_LENGTH];
	char	*args[MAX_ARGS];
	int		arg_count;

	while (1)
	{
		printf("minishell> ");
		if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\nExiting minishell\n");
			break ;
		}
		// Remove the newline character from the end of the input
		input[strcspn(input, "\n")] = '\0';
		arg_count = parse_command(input, args);
		if (arg_count > 0)
		{
			execute_command(args);
		}
	}
	return (0);
}
