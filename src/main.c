/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 13:05:19 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

int	execution(t_list *tabel)
{
	int	result;
	int	orig_stdin;
	int	orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(tabel))
	{
		restore_std_fds(orig_stdin, orig_stdout);
		return (1);
	}
	if (ft_lstsize(tabel) > 1)
		result = execute_piped_commands(tabel);
	else
		result = execute_command(tabel);
	restore_std_fds(orig_stdin, orig_stdout);
	return (result);
}

static void	process_command_main(char *input)
{
	t_list	*tokens;
	t_list	*tabel;
	t_list	*new_tabel;

	handle_history(input);
	tokens = parse_input(input);
	if (tokens == NULL)
		return ;
	tabel = create_tabel(tokens);
	new_tabel = expansion(tabel);
	execution(new_tabel);
	ft_lstclear(&tokens, free_token);
	ft_lstclear(&tabel, free_tabel);
}

void	main_loop(void)
{
	char	*input;

	while (1)
	{
		g_signal = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input[0] != '\0')
			process_command_main(input);
		free(input);
	}
	printf("exit\n");
}

void	check_l(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (*env_vars() == NULL)
		*env_vars() = copy_envp(envp);
	if (!env_vars())
		return (perror("Failed to copy envp"), 1);
	*exit_status() = 0;
	*is_expanded() = 0;
	handle_shlvl();
	handle_signals();
	main_loop();
}
