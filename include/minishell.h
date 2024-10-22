/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:08:07 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/22 13:37:52 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/get_next_line.h"
# include "../lib/libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_ARGS 1024

extern int			g_signal;

typedef enum s_builtin_type
{
	NONE,
	EXIT,
	PWD,
	CD,
	ENV,
	EXPORT,
	UNSET,
	ECHO
}					t_builtin_type;

typedef struct s_info
{
	int				nbr_words;
	int				nbr_reds;
	int				nbr_filenames;
	size_t			blocks;
	t_list			*table;
	t_list			*tmp;
	t_list			*tmp2;
}					t_info;

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

typedef enum e_token_type
{
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HERE,
	TOKEN_WORD
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
}					t_token;

typedef struct s_command
{
	char			**args;
	char			**filename;
	char			**red_symbol;
}					t_command;

//----- parsing -----
// create_linked_list
void				free_token(void *content);
int					create_linked_list(char **tokens, t_list **list);

// create_tabel
t_info				*init_info(void);
size_t				count_lines(t_list *tokens);
void				process_command(t_info *info);
t_list				*free_info_return_table(t_info *info);
t_list				*create_tabel(t_list *tokens);
// create_tabel2
t_command			*init_cmd(void);
int					is_redirection_tabel(t_token *current_token);
void				reset_info(t_info *info);
void				count_words_redirections(t_list **tokens, t_info *info);
// create_tabel3
t_command			*allocate_cmd(t_command *new_cmd, t_list *token_position,
						t_info *info);
void				process_redirection(t_command *cmd, t_list **tmp,
						size_t *j);
;
void				process_argument(t_command *cmd, t_token *current_token,
						size_t *i);
t_command			*fill_cmd(t_command *cmd, t_list *position);

// expand_env
char				*expand_env_variables(char *src);
// expand_process_arg
void				process_arg(t_command *cmd, size_t *i);
// expand_quotes
void				remove_quotes(t_command *cmd);
// expand
char				*get_our_env(const char *name);
void				remove_empty_arg(t_command *row, size_t *i);
;
void				handle_expansion(t_command *cmd);
t_list				*expansion(t_list *tabel);
// expand2
size_t				get_result_len(char *result);
char				*copy_until_dollar(char **result, char *start, char *end);
;
char				*get_var_name(char **end);
char				*append_var_value(char **result, char *var_value);
char				*handle_dollar(char **result, char **start, char **end);

// parsing_handler
void				handle_non_specials(t_trim *trim, char *input);
void				handle_operator(t_trim *trim, char *input);
void				handle_quotes(t_trim *trim, char *input);
void				handle_specials(t_trim *trim, char *input);
// parsing
void				trim_str(t_trim *trim, char *input);
char				*trim_whitespace(char *input);
void				*check_syntax(char *input);
t_list				*parse_input(char *input);

// process_token
bool				command_exists(const char *command);
void				fill_struct(t_token *token, char *content);

// split_quotes
char				**split_space_quotes(const char *input);
void				free_token_array(char **tokens);
// split_quotes2
size_t				count_tokens(const char *str);
char				*extract_token(const char *str, size_t *pos);

// syntax_errors
char				*handle_syntax_errors(const char *input);

// trim_len
int					ft_trim_len(char *input);
// trim_len2
bool				is_special_char(char c);

//---- builtins ----
// cd
int			ft_cd(char *argv[], int argc);

// echo
int	ft_echo(char *argv[], int argc);

// env
int		env(void);
char	**copy_envp(char **envp);
void	free_env(char **my_envp);

// export_utils
int	is_valid_identifier(const char *str);
char	**copy_env(char **envp, int count);
int	count_env_vars(char **envp);
void	bubble_sort_env(char **envp, int count);
int	compare_env(const void *a, const void *b);
// export_utils2
int	set_export_error(char *name, char *value);
int	add_or_update_env(char *name, char *value);
char	*create_new_var(char *new_var, const char *name, char *value);
int	add_new_env_var(const char *name, char *value, int i);
// export
int	ft_export(char **args, int arg_count);
int ft_export_args(char *arg);
int	mark_for_export(const char *name);
int	print_sorted_env(void);

// pwd
int	pwd(void);

// unset
int	ft_unset(char *argv[], int argc);




// --- execution ---
int					*is_expanded(void);
char				*expand_env_variables(char *src);
char				*handle_dollar(char **result, char **start, char **end);
char				*copy_until_dollar(char **result, char *start, char *end);
void				remove_quotes(t_command *cmd);
int					ft_exit(char *args[]);
int					execute_command(t_list *tabel);
void				handle_operator(t_trim *trim, char *input);
void				handle_specials(t_trim *trim, char *input);
void				fill_struct(t_token *token, char *content);
int					create_linked_list(char **tokens, t_list **list);
void				print_token_list(t_list *list);
void				free_token(void *content);
void				print_struct_tabel(t_list *tabel);
t_list				*create_tabel(t_list *token_list);
void				print_tabel(t_list *tabel);
int					ft_exit(char *args[]);
void				handle_shlvl(void);
char				*expand_env_variables(char *src);
int					ft_trim_len(char *input);

// execute_external_utils
int					handle_command_not_found(char **args);
int					handle_parent_process(pid_t pid, char *command_path);
void				ft_errorcode_exit(char *command, char *path);

// fake globals
int					*exit_status(void);
char				***env_vars(void);
// history
void				clear_shell_history(void);
void	handle_history(char *input);
// path
char				*search_path(const char *file);
int					execute_external_command(char **args);
// pipes
int					execute_piped_commands(t_list *command_list);
int					is_builtin(t_command *cmd);
void				exec_builtin(t_command *cmd, int builtin);
// pipes_utils
void				close_pipes(int pipe_fds[][2], int num_pipes);
int					fork_and_execute(int pipe_fds[][2], t_list *current, int i,
						int num_commands);
int					wait_for_children(void);
int					setup_child_pipes(int pipe_fds[][2], int i,
						int num_commands);
// redirection
int					redirect_input(char *file);
int					redirect_output(char *file, int append);
int					handle_heredoc(char *delimiter);
int					handle_redirections(t_list *command_list);
// redirection utils
void				restore_std_fds(int orig_stdin, int orig_stdout);
int					is_redirection(char *symbol);
void				print_redirection_error(char *filename, char *error_msg);
int					apply_single_redirection(char *symbol, char *filename);
int					apply_redirections(t_command *cmd);
// signals
void				sigint_handler(int sig);
void				handle_signals(void);
// utils
int					strcasecmp_custom(const char *s1, const char *s2);
void				free_tabel(void *content);
// main
int					execution(t_list *tabel);
int					exec_new_shell(char **argv);
void				main_loop(void);
void				handle_shlvl(void);
t_list				*parse_input(char *input);


#endif
