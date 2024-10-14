/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/14 13:08:42 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

void	free_command(void *content)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *)content;
	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->filename)
	{
		i = 0;
		while (cmd->filename[i])
		{
			free(cmd->filename[i]);
			i++;
		}
		free(cmd->filename);
	}
	if (cmd->red_symbol)
	{
		i = 0;
		while (cmd->red_symbol[i])
		{
			free(cmd->red_symbol[i]);
			i++;
		}
		free(cmd->red_symbol);
	}
	free(cmd);
}

int	create_child_process(t_list *tmp, int in_fd, int *pipefd)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (tmp->next != NULL)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	execute_command(tmp);
	exit(0);
}

void	execute_right_child(pid_t pid, int *in_fd, int *pipefd, t_list *tmp)
{
	waitpid(pid, NULL, 0);
	if (*in_fd != 0)
		close(*in_fd);
	if (tmp->next != NULL)
		close(pipefd[1]);
	*in_fd = pipefd[0];
}

int	execute_pipe(t_list *tabel)
{
	t_list	*tmp;
	int		pipefd[2];
	pid_t	pid;
	int		in_fd;

	in_fd = 0;
	tmp = tabel;
	while (tmp != NULL)
	{
		if (tmp->next != NULL && pipe(pipefd) == -1)
			return (write(2, "pipe failed\n", 12), 1);
		pid = fork();
		if (pid == -1)
			return (write(2, "fork failed\n", 12), 1);
		if (pid == 0)
		{
			if (create_child_process(tmp, in_fd, pipefd))
				return (1);
		}
		else
		{
			execute_right_child(pid, &in_fd, pipefd, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	execute_tabel(t_list *tabel)
{
	t_list		*tmp;
	t_command	*cmd;

	tmp = tabel;
	cmd = (t_command *)tmp->content;
	if (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			// write(1, "pipe\n\n", 5);
			execute_pipe(tmp);
		}
		else if (cmd->args != NULL)
			execute_command(tmp);
	}
	return (0);
}

void	main_loop(void)
{
	char	*input;
	t_list	*tokens;
	t_list	*tabel;
	char	*trimmed_input;

	while (1)
	{
		g_signal = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		trimmed_input = trim_whitespace(input);
		free(input);
		if (!trimmed_input)
			continue ;
		if (strcmp(trimmed_input, "$?") == 0)
		{
			printf("%d\n", *exit_status());
			free(trimmed_input);
			continue ;
		}
		handle_history(trimmed_input);
		tokens = parse_input(trimmed_input);
		free(trimmed_input);
		if (tokens)
		{
			tabel = create_tabel(tokens);
			if (tabel)
			{
				execute_tabel(tabel);
				ft_lstclear(&tabel, free_command);
			}
			ft_lstclear(&tokens, free_token);
		}
	}
	printf("exit\n");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (*env_vars() == NULL)
		*env_vars() = copy_envp(envp);
	if (!env_vars())
		return (perror("Failed to copy envp"), 1);
	set_env_vars(*env_vars());
	handle_shlvl();
	handle_signals();
	main_loop();
	free_env(*env_vars());
	return (*exit_status());
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
}

int	ft_exit(char *args[], int arg_count)
{
	long long	exit_code;
	char		*arg;
	int			i;
	int			is_valid;

	exit_code = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (arg_count > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (arg_count == 2)
	{
		arg = args[1];
		i = 0;
		while (ft_isspace(arg[i]))
			i++;
		if (arg[i] == '+' || arg[i] == '-')
		{
			i++;
		}
		is_valid = 1;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
			{
				is_valid = 0;
				break ;
			}
			i++;
		}
		exit_code = ft_atol(args[1]);
		if (!is_valid || (exit_code > INT_MAX || exit_code < INT_MIN))
		{
			ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
			exit(255);
		}
	}
	exit((int)(exit_code & 0xFF));
}
