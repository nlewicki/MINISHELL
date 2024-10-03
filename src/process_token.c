/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:08:26 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/03 11:01:40 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_struct(t_token *token, char *content)
{
	if (ft_strncmp(content, ">>", 2) == 0)
		token->type = TOKEN_REDIR_APPEND;
	else if (ft_strncmp(content, ">", 1) == 0)
		token->type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(content, "<<", 2) == 0)
		token->type = TOKEN_REDIR_HERE;
	else if (ft_strncmp(content, "<", 1) == 0)
		token->type = TOKEN_REDIR_IN;
	else if (ft_strncmp(content, "|", 1) == 0)
		token->type = TOKEN_PIPE;
	// else if $ -> variable
	else
		token->type = TOKEN_WORD;
	token->content = ft_strdup(content);
}
