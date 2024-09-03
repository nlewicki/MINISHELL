/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:41 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/02 12:53:11 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void	strip_quotes(char *str)
{
	char	*end;
	char	*src;
	char	*dst;

	end = str;
	while (*end)
		end++; // Find the end of the string
	end--;     // Move back to the last character
	if (end > str) // Ensure the string has at least 2 characters
	{
		if ((str[0] == '"' && *end == '"') || (str[0] == '\'' && *end == '\''))
		{
			src = str + 1;
			dst = str;
			while (src < end)
			{
				*dst = *src;
				dst++;
				src++;
			}
			*dst = '\0';
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
			token_start = input + 1; // Start token after the opening quote
		}
		else if (*input == quote_char && in_quotes)
		{
			in_quotes = 0;
			*input = '\0'; // Null-terminate the argument
			args[arg_count++] = token_start;
			token_start = input + 1;
		}
		else if (isspace(*input) && !in_quotes)
		{
			if (token_start != input)
			{
				*input = '\0';
				args[arg_count++] = token_start;
			}
			token_start = input + 1;
		}
		input++;
	}
	// Handle the last argument if it exists
	if (token_start != input && arg_count < MAX_ARGS)
	{
		args[arg_count++] = token_start;
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

int	strcasecmp_custom(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
			return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
		s1++;
		s2++;
	}
	return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2));
}

int	execute_command(char *args[], int arg_count)
{
	if (strcasecmp_custom(args[0], "pwd") == 0)
	{
		if (arg_count > 1)
		{
			fprintf(stderr, "pwd: too many arguments\n");
			return (1);
		}
		return (pwd(arg_count));
	}
	// Add other built-in commands here
	// If not a built-in command, you can add logic to execute external commands
	printf("Command not found: %s\n", args[0]);
	return (1);
}

int	main(void)
{
	char	*input;
	char	*args[MAX_ARGS];
	int		arg_count;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("\nExiting minishell\n");
			break ;
		}
		// Add input to history if it's not empty
		if (strlen(input) > 0)
		{
			add_history(input);
		}
		arg_count = parse_command(input, args);
		if (arg_count > 0)
		{
			if (strcasecmp_custom(args[0], "history-clear") == 0)
			{
				rl_clear_history();
			}
			else
			{
				execute_command(args, arg_count);
			}
		}
		// Free the memory allocated by readline
		free(input);
	}
	// Clear the history when exiting
	rl_clear_history();
	return (0);
}
