/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/17 13:39:35 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

void	main_loop(void)
{
	char	*input;
	t_list	*tokens;
	t_list	*tabel;

	while (1)
	{
		g_signal = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		handle_history(input);
		tokens = parse_input(input);
		// print_token_list(tokens);
		tabel = create_tabel(tokens);
		print_tabel(tabel);
		expansion(tabel);
		execute_command(tabel);
		free(input);
		ft_lstclear(&tokens, free_token);
		ft_lstclear(&tabel, free_token);
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

	// debugg
	char **env = *env_vars();
	for (int i = 0; env[i]; i++)
		printf("env[%d]: %s\n", i, env[i]);
	printf("\nPATH: %s\n", get_our_env("PATH"));

	handle_shlvl();
	handle_signals();
	main_loop();
	free_env(*env_vars());
	return (*exit_status());
}
