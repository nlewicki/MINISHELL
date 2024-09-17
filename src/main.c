/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:52:41 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/17 13:13:59 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

int	parse_redirections(char *input, t_redirection *redirections,
		int *redirection_count)
{
	char	*token;
	char	*saveptr;

	*redirection_count = 0;
	token = ft_strtok_r(input, " \t", &saveptr);
	while (token != NULL && *redirection_count < MAX_REDIRECTIONS)
	{
		if (ft_strcmp(token, "<") == 0)
			redirections[*redirection_count].type = 0;
		else if (ft_strcmp(token, ">") == 0)
			redirections[*redirection_count].type = 1;
		else if (ft_strcmp(token, "<<") == 0)
			redirections[*redirection_count].type = 2;
		else if (ft_strcmp(token, ">>") == 0)
			redirections[*redirection_count].type = 3;
		else
		{
			token = ft_strtok_r(NULL, " \t", &saveptr);
			continue ;
		}
		token = ft_strtok_r(NULL, " \t", &saveptr);
		if (token == NULL)
		{
			write(2, "Error: Missing argument for redirection\n", 39);
			return (1);
		}
		redirections[*redirection_count].file = ft_strdup(token);
		(*redirection_count)++;
		token = ft_strtok_r(NULL, " \t", &saveptr);
	}
	return (0);
}

int	apply_redirections(t_redirection *redirections, int redirection_count)
{
	int		fd;
	int		pipe_fd[2];
	char	*line;
	size_t	len;
	ssize_t	read;
	int		i;

	i = 0;
	while (i < redirection_count)
	{
		switch (redirections[i].type) // switch und case ersetzen
		{
		case 0: // <
		{
			fd = open(redirections[i].file, O_RDONLY);
			if (fd < 0)
			{
				perror("Error opening input file");
				return (1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("Error redirecting input");
				close(fd);
				return (1);
			}
			close(fd);
		}
		break ;
		case 1: // >
		{
			fd = open(redirections[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("Error opening output file");
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		break ;
		case 2: // <<
		{
			if (pipe(pipe_fd) < 0)
			{
				perror("Error creating pipe");
				return (1);
			}
			line = NULL;
			len = 0;
			while ((read = getline(&line, &len, stdin)) != -1)
				// getline ersetzen
			{
				if (ft_strcmp(line, redirections[i].file) == 0)
				{
					break ;
				}
				write(pipe_fd[1], line, read);
			}
			free(line);
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		}
		break ;
		case 3: // >>
		{
			fd = open(redirections[i].file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (fd < 0)
			{
				perror("Error opening output file for appending");
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		break ;
		}
		i++;
	}
	return (0);
}

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
