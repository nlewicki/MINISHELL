/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:41 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/16 12:40:34 by nlewicki         ###   ########.fr       */
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
	int		in_single_quotes;
	char	*expanded;

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
			input++;
			args[arg_count++] = ft_strndup(token_start, input - token_start);
			token_start = input;
		}
		else if (ft_isspace(*input) && !in_quotes)
		{
			if (token_start != input)
			{
				args[arg_count++] = ft_strndup(token_start, input
						- token_start);
			}
			token_start = input + 1;
		}
		if (*input != '\0')
			input++;
	}
	if (token_start != input && arg_count < MAX_ARGS)
	{
		if (in_quotes)
			args[arg_count++] = ft_strndup(token_start, input - token_start);
		else
			args[arg_count++] = ft_strdup(token_start);
	}
	args[arg_count] = NULL;
	i = 0;
	while (i < arg_count)
	{
		if (args[i][0] == '\'' && args[i][strlen(args[i]) - 1] == '\'')
		{
			memmove(args[i], args[i] + 1, strlen(args[i]) - 2);
			args[i][strlen(args[i]) - 2] = '\0';
		}
		else
		{
			in_single_quotes = 0;
			if (args[i][0] == '"' && args[i][strlen(args[i]) - 1] == '"')
			{
				memmove(args[i], args[i] + 1, strlen(args[i]) - 2);
				args[i][strlen(args[i]) - 2] = '\0';
			}
			expanded = expand_env_variables(args[i], in_single_quotes);
			free(args[i]);
			args[i] = expanded;
		}
		i++;
	}
	return (arg_count);
}

int	execute_command(char *args[], int arg_count)
{
	int	result;

	if (strcmp(args[0], "exit") == 0)
		exit(*exit_status());
	else if (strcasecmp_custom(args[0], "pwd") == 0)
		return (pwd());
	else if (strcasecmp_custom(args[0], "env") == 0)
		return (env());
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
		*exit_status() = result;
		if (result != 0)
			printf("%s: command not found\n", args[0]);
		return (result);
	}
	return (0);
}

void	main_loop(void)
{
	char	*input;
	char	*commands[MAX_ARGS];
	int		num_commands;
	char	*argv[MAX_ARGS];
	int		argc;
	int		i;

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
		num_commands = 0;
		commands[num_commands] = strtok(input, "|");
		while (commands[num_commands] != NULL && num_commands < MAX_ARGS - 1)
		{
			num_commands++;
			commands[num_commands] = strtok(NULL, "|");
		}
		if (num_commands > 1)
		{
			*exit_status() = execute_piped_commands(commands, num_commands);
		}
		else if (num_commands == 1)
		{
			argc = parse_command(commands[0], argv);
			if (argc > 0)
			{
				*exit_status() = execute_command(argv, argc);
			}
		}
		i = 0;
		while (i < argc)
		{
			free(argv[i]);
			i++;
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
