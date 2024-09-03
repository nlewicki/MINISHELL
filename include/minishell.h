/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:08:07 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/03 10:13:02 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

#define MAX_ARGS 100
#define MAX_COMMAND_LENGTH 1000

extern int	g_signal;

// builtins
int pwd(int argc);


// signals
void sigint_handler(int sig);
void handle_signals(void);

// globals
int *exit_status(void);

// parsing
int parse_command(char *input, char *args[]);
int strcasecmp_custom(const char *s1, const char *s2);
int execute_command(char *args[], int arg_count);

#endif
