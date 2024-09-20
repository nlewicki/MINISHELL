/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:41 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/19 13:45:03 by mhummel          ###   ########.fr       */
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
	char	*expanded;
	int		in_single_quotes;

	arg_count = 0;
	in_quotes = 0;
	quote_char = 0;
	in_single_quotes = 0;
	while (*input != '\0' && arg_count < MAX_ARGS - 1)
	{
		while (*input == ' ' || *input == '\t')
			input++;
		if (*input == '<' || *input == '>')
			break ;
		token_start = input;
		while (*input != '\0' && (in_quotes || (*input != ' '
					&& *input != '\t')))
		{
			if (*input == '"' || *input == '\'')
			{
				if (!in_quotes)
				{
					in_quotes = 1;
					quote_char = *input;
					in_single_quotes = (*input == '\'');
				}
				else if (*input == quote_char)
				{
					in_quotes = 0;
				}
			}
			input++;
		}
		if (token_start != input)
		{
			args[arg_count] = ft_strndup(token_start, input - token_start);
			if (!args[arg_count])
				return (-1);
			if (args[arg_count][0] == quote_char
				&& args[arg_count][ft_strlen(args[arg_count])
				- 1] == quote_char)
			{
				memmove(args[arg_count], args[arg_count] + 1,
					ft_strlen(args[arg_count]) - 2);
				args[arg_count][ft_strlen(args[arg_count]) - 2] = '\0';
			}
			if (!in_single_quotes)
			{
				expanded = expand_env_variables(args[arg_count],
						in_single_quotes);
				if (!expanded)
				{
					free(args[arg_count]);
					return (-1);
				}
				free(args[arg_count]);
				args[arg_count] = expanded;
			}
			arg_count++;
		}
		if (*input != '\0')
			input++;
	}
	args[arg_count] = NULL;
	return (arg_count);
}

int	exec_new_shell(char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve("./minishell", argv, *env_vars());
		perror("execve failed");
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (status);
	}
	else
	{
		perror("fork failed");
		return (1);
	}
}

int	execute_command(char *args[], int arg_count, t_redirection *redirections,
		int redirection_count)
{
	int	result;
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(redirections, redirection_count) != 0)
	{
		return (1);
	}
	if (ft_strcmp(args[0], "exit") == 0)
	{
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
		exit(*exit_status());
	}
	else if (strcasecmp_custom(args[0], "pwd") == 0)
		result = pwd();
	else if (strcasecmp_custom(args[0], "env") == 0)
		result = env();
	else if (strcasecmp_custom(args[0], "echo") == 0)
		result = ft_echo(args, arg_count);
	else if (strcasecmp_custom(args[0], "unset") == 0)
		result = ft_unset(args, arg_count);
	else if (strcasecmp_custom(args[0], "cd") == 0)
		result = ft_cd(args, arg_count);
	else if (strcasecmp_custom(args[0], "export") == 0)
		result = ft_export(args, arg_count);
	else if (strcasecmp_custom(args[0], "./minishell") == 0)
		result = exec_new_shell(args);
	else
	{
		result = execute_external_command(args);
		*exit_status() = result;
		if (result != 0)
			printf("%s: command not found\n", args[0]);
	}
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (result);
}

void	main_loop(void)
{
	char			*input;
	char			*commands[MAX_ARGS];
	int				num_commands;
	char			*argv[MAX_ARGS];
	int				argc;
	int				i;
	t_redirection	redirections[MAX_REDIRECTIONS];
	int				redirection_count;
	char			*command_copy;

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
		if (ft_strlen(input) > 0)
			add_history(input);
		num_commands = 0;
		commands[num_commands] = ft_strtok(input, "|");
		while (commands[num_commands] != NULL && num_commands < MAX_ARGS - 1)
		{
			num_commands++;
			commands[num_commands] = ft_strtok(NULL, "|");
		}
		if (num_commands > 1)
		{
			*exit_status() = execute_piped_commands(commands, num_commands);
		}
		else if (num_commands == 1)
		{
			command_copy = ft_strdup(commands[0]);
			if (parse_redirections(command_copy, redirections,
					&redirection_count) != 0)
			{
				free(command_copy);
				free(input);
				continue ;
			}
			argc = parse_command(commands[0], argv);
			if (argc > 0)
			{
				*exit_status() = execute_command(argv, argc, redirections,
						redirection_count);
			}
			free(command_copy);
			i = 0;
			while (i < redirection_count)
			{
				free(redirections[i].file);
				i++;
			}
		}
		i = 0;
		while (i < argc)
		{
			if (argv[i] != NULL)
			{
				free(argv[i]);
				argv[i] = NULL;
			}
			i++;
		}
		free(input);
	}
	rl_clear_history();
}

void	handle_shlvl(void)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = get_our_env("SHLVL");
	if (!shlvl_str)
		shlvl = 0;
	else
		shlvl = atoi(shlvl_str);
	shlvl += 1;
	add_or_update_env("SHLVL", ft_itoa(shlvl));
	// printf("Updated SHLVL to %d\n", shlvl);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (*env_vars() == NULL)
	{
		*env_vars() = copy_envp(envp);
		// printf("Copied envp to env_vars\n");
	}
	if (!env_vars())
		return (perror("Failed to copy envp"), 1);
	set_env_vars(*env_vars());
	handle_shlvl();
	// char *current_shlvl = get_our_env("SHLVL");
	// printf("Current SHLVL: %s\n", current_shlvl ? current_shlvl : "Not set");
	handle_signals();
	main_loop();
	free_env(*env_vars());
	return (*exit_status());
}
