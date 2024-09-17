/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:08:07 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/17 12:53:52 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX_ARGS 100
# define MAX_REDIRECTIONS 10

extern int	g_signal;

typedef struct s_redirection {
	int type;  // 0: <, 1: >, 2: <<, 3: >>
	char *file;
} t_redirection;

// builtins
int			pwd(void);
int			ft_echo(char *argv[], int argc);
int			env(void);
char		**copy_env(char **envp, int count);
int			ft_cd(char *argv[], int argc);
int			ft_unset(char *argv[], int argc);
int			ft_export(char **args, int arg_count);

int			add_new_env_var(const char *name, char *value, int i);
int			mark_for_export(const char *name);
int			compare_env(const void *a, const void *b);
void		bubble_sort_env(char **envp, int count);
int			count_env_vars(char **envp);
int			is_valid_identifier(const char *str);
int			add_or_update_env(char *name, char *value);

// expand
char		*expand_env_variables(char *src, int in_single_quotes);
char 		*get_our_env(char *var_name);

// signals
void		sigint_handler(int sig);
void		handle_signals(void);

// globals
int			*exit_status(void);
char		***env_vars(void);
void		set_env_vars(char **envp);
void		free_env(char **my_envp);

// parsing
int			parse_command(char *input, char *args[]);
int			strcasecmp_custom(const char *s1, const char *s2);
char		**copy_envp(char **envp);
void		strip_quotes(char *str);

int			execute_external_command(char **args);
char		*search_path(const char *file);

int			execute_piped_commands(char *commands[], int num_commands);
char		*expand_env_variables(char *input, int in_single_quotes);


int			execute_command(char *args[], int arg_count, t_redirection *redirections, int redirection_count);

int			parse_redirections(char *input, t_redirection *redirections, int *redirection_count);
int			apply_redirections(t_redirection *redirections, int redirection_count);

#endif
