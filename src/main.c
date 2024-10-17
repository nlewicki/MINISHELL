/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/17 09:48:13 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

int	execute_tabel(t_list *tabel);

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
	// t_list	*tabel;

	while (1)
	{
		g_signal = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		handle_history(input);
		tokens = parse_input(input);
		print_token_list(tokens);
		// tabel = create_tabel(tokens);
		// print_tabel(tabel);
		// execute_tabel(tabel);
		free(input);
		ft_lstclear(&tokens, free_token);
		// ft_lstclear(&tabel, free_token);
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

int	ft_exit(char *args[])
{
	int	exit_code;

	exit_code = 0;
	if (args[1] != NULL)
	{
		if (!ft_atoi(args[1]) || ft_strlen(args[1]) == 0)
		{
			ft_putendl_fd("exit", 2);
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			exit(255);
		}
		if (args[2])
		{
			ft_putendl_fd("exit", 2);
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			*exit_status() = 1;
		}
		exit_code = ft_atoi(args[1]);
		exit_code = exit_code % 256;
	}
	*exit_status() = exit_code;
	ft_putendl_fd("exit", 2);
	exit(exit_code);
}
