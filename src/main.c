/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:41 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/03 11:21:53 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

void	strip_quotes(char *str)
{
	char	*end;
	char	*src;
	char	*dst;

	end = str;
	while (*end)
		end++;
	end--;
	if (end > str)
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
			write(2, "pwd: too many arguments\n", 24);
			return (1);
		}
		return (pwd(arg_count));
	}
	if (strcmp(args[0], "exit") == 0)
	{
		*exit_status() = 1;
		exit(0);
	}
	if (strcasecmp_custom(args[0], "echo") == 0)
	{
		return(ft_echo(args, arg_count));
	}
	// Add other built-in commands here
	// If not a built-in command, you can add logic to execute external commands
	printf("Command not found: %s\n", args[0]);
	return (1);
}
void	main_loop(void)
{
	char	*input;
	char	*argv[MAX_ARGS];
	int		argc;

	while (1)
	{
		g_signal = 0;
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal)
		{
			free(input);
			continue ;
		}
		if (strlen(input) > 0)
			add_history(input);
		argc = parse_command(input, argv);
		if (argc > 0)
		{
			execute_command(argv, argc);
		}
		free(input);
	}
	rl_clear_history();
}

int	main(void)
{
	handle_signals();
	main_loop();
	return (*exit_status());
}
