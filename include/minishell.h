/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:08:07 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/04 12:04:40 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/get_next_line.h"
# include "../lib/libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define MAX_ARGS 100
# define MAX_REDIRECTIONS 10

extern int			g_signal;

typedef struct s_redirection
{
	int				type;
	char			*file;
}					t_redirection;

typedef struct s_trim
{
	char			*result;
	size_t			i;
	size_t			j;
	size_t			len;
	bool			is_space;
	bool			error;
}					t_trim;

typedef enum
{
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HERE,
	TOKEN_VARIABLE,
	TOKEN_WORD,
	TOKEN_COMMAND,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
}					t_token;

void	handle_operator(t_trim *trim, char *input);
void	handle_quotes(t_trim *trim, char *input);
void	handle_specials(t_trim *trim, char *input);
void	handle_history(char *input);
void				fill_struct(t_token *token, char *content, bool *command);

// builtins
// cd
int					ft_cd(char *argv[], int argc);
// echo
int					ft_echo(char *argv[], int argc);
// env
int					env(void);
void				set_env_vars(char **envp);
char				**copy_envp(char **envp);
void				free_env(char **my_envp);
// export
int					print_sorted_env(void);
int					mark_for_export(const char *name);
int					ft_export_args(char *arg);
int					ft_export(char **args, int arg_count);
// export_utils
int					compare_env(const void *a, const void *b);
void				bubble_sort_env(char **envp, int count);
int					count_env_vars(char **envp);
char				**copy_env(char **envp, int count);
int					is_valid_identifier(const char *str);
// export_utils2
int					add_new_env_var(const char *name, char *value, int i);
char				*create_new_var(char *new_var, const char *name,
						char *value);
int					add_or_update_env(char *name, char *value);
int					set_export_error(char *name, char *value);
// pwd
int					pwd(void);
// unset
int					ft_unset(char *argv[], int argc);
// expand
char				*get_our_env(const char *var_name);
void				handle_expansion(size_t *length, const char **src);
size_t				calculate_expanded_length(const char *src,
						int in_single_quotes);
char				*expand_env_variables(char *src, int in_single_quotes);
// fake globals
int					*exit_status(void);
char				***env_vars(void);
// history
void				clear_shell_history(void);
// path
char				*search_path(const char *file);
int					execute_external_command(char **args);
// pipes
int					execute_piped_commands(char *commands[], int num_commands);
// redirection
int					parse_redirections(char *input, t_redirection *redirections,
						int *redirection_count);
int					redirect_input(char *file);
int					redirect_output(char *file, int flags);
int					handle_heredoc(char *delimiter);
int					apply_redirections(t_redirection *redirections,
						int redirection_count);
// signals
void				sigint_handler(int sig);
void				handle_signals(void);
// utils
void				strip_quotes(char *str);
int					strcasecmp_custom(const char *s1, const char *s2);

// main
int					parse_command(char *input, char *args[]);
int					exec_new_shell(char **argv);
int					execute_command(char *args[], int arg_count,
						t_redirection *redirections, int redirection_count);
void				main_loop(void);
void				handle_shlvl(void);
int					parse_input(char *input);
void				handle_history(char *input);

// split quotes
void				free_token_array(char **tokens);
char				**split_space_quotes(const char *input);

#endif
