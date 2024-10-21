/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/21 13:08:40 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

void free_tabel(void *content)
{
	t_command *cmd = (t_command *)content;
	size_t i;

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

void	main_loop(void)
{
	char	*input;
	t_list	*tokens;
	t_list	*tabel;
	t_list	*new_tabel;

	while (1)
	{
		g_signal = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		else if (input[0] != '\0')
		{
			handle_history(input);
			tokens = parse_input(input);
			if (tokens == NULL)
			{
				free(input);
				continue ;
			}
			// print_token_list(tokens);
			tabel = create_tabel(tokens);
			// print_tabel(tabel);
			new_tabel = expansion(tabel);
			// print_tabel(new_tabel);
			execution(new_tabel);
			free(input);
			ft_lstclear(&tokens, free_token);
			ft_lstclear(&tabel, free_tabel);
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

	// debugg
	// char **env = *env_vars();
	// for (int i = 0; env[i]; i++)
	// 	printf("env[%d]: %s\n", i, env[i]);
	// printf("\nPATH: %s\n", get_our_env("PATH"));
	*exit_status() = 0;
	handle_shlvl();
	handle_signals();
	main_loop();
	free_env(*env_vars());
	// return (*exit_status());
}
