/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/14 09:57:22 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	nbr_of_args(char **str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (CD);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ENV);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (EXIT);
	else
		return (NONE);
}

int	exec_builtin(t_command *cmd, int builtin)
{
	write(1, "Executing builtin\n\n", 19);
	if (builtin == CD)
		ft_cd(cmd->args, nbr_of_args(cmd->args));
	else if (builtin == PWD)
		pwd();
	else if (builtin == ECHO)
		ft_echo(cmd->args, nbr_of_args(cmd->args));
	else if (builtin == ENV)
		env();
	else if (builtin == UNSET)
		ft_unset(cmd->args, nbr_of_args(cmd->args));
	else if (builtin == EXPORT)
		ft_export(cmd->args, nbr_of_args(cmd->args));
	return (0);
}

int	g_signal = 0;

int execute_command(t_list *tabel)
{
	t_list	*tmp;
	int		builtin;

	tmp = tabel;
	builtin = is_builtin((t_command *)tmp->content);
	if (builtin)
		exec_builtin((t_command *)tmp->content, builtin);
	else
		write(1, "Not a builtin\n", 14);
	return (0);
}

void	main_loop(void)
{
	char *input;
	t_list *tokens;
	t_list *tabel;

	while (1)
	{
		g_signal = 0;
		input = readline("minishell> ");
		if (!input)
			break ;

		handle_history(input);
		tokens = parse_input(input);
		print_token_list(tokens);
		tabel = create_tabel(tokens);
		print_tabel(tabel);
		execute_command(tabel); // add data?
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
