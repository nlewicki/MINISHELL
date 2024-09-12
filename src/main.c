/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:41 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/12 13:37:59 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

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
			token_start = input + 1;
		}
		else if (*input == quote_char && in_quotes)
		{
			in_quotes = 0;
			*input = '\0';
			args[arg_count++] = token_start;
			token_start = input + 1;
		}
		else if (ft_isspace(*input) && !in_quotes)
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
	if (token_start != input && arg_count < MAX_ARGS)
	{
		if (in_quotes)
			*(input - 1) = '\0';
		args[arg_count++] = token_start;
	}
	args[arg_count] = NULL;
	i = 0;
	while (i < arg_count)
	{
		strip_quotes(args[i]);
		i++;
	}
	return (arg_count);
}

int	execute_command(char *args[], int arg_count)
{
	int	result;

	if (strcasecmp_custom(args[0], "pwd") == 0)
		return (pwd());
	else if (strcmp(args[0], "exit") == 0)
	{
		// *exit_status() = 1;
		exit(0);
	}
	else if (strcasecmp_custom(args[0], "env") == 0)
	{
		if (arg_count > 1)
			return (1);
		return (env());
	}
	else if (strcasecmp_custom(args[0], "echo") == 0)
		return (ft_echo(args, arg_count));
	else if (strcasecmp_custom(args[0], "unset") == 0)
		return (ft_unset(args, arg_count));
	else if (strcasecmp_custom(args[0], "cd") == 0)
		return (ft_cd(args, arg_count));
	else if (strcasecmp_custom(args[0], "export") == 0)
		return (ft_export(args, arg_count));
	else
	{
		result = execute_external_command(args);
		if (result != 0)
			printf("%s: command not found\n", args[0]);
		return (result);
	}
	return (0);
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

int	main(int argc, char **argv, char **envp)
{
	char	**my_envp;

	(void)argc;
	(void)argv;
	my_envp = copy_envp(envp);
	if (!my_envp)
		return (perror("Failed to copy envp"), 1);
	set_env_vars(my_envp);
	handle_signals();
	main_loop();
	free_env(my_envp);
	return (*exit_status());
}
