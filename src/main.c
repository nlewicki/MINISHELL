/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/14 10:00:06 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

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
