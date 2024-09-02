/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:08:07 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/02 13:32:16 by mhummel          ###   ########.fr       */
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

#define MAX_ARGS 100  // Stellen Sie sicher, dass diese Konstante definiert ist
#define MAX_COMMAND_LENGTH 1000  // Stellen Sie sicher, dass diese Konstante definiert ist

// Existierende Funktionsprototypen
int pwd(int argc);
// ... andere Funktionsprototypen ...

// Signalbehandlung und Eingabe
void setup_signal_handlers(void);
int handle_signals(char *input);

// Befehlsverarbeitung
int parse_command(char *input, char *args[]);
int strcasecmp_custom(const char *s1, const char *s2);
int execute_command(char *args[], int arg_count);

// Wenn Sie weitere Funktionen haben, fügen Sie ihre Deklarationen hier hinzu

#endif