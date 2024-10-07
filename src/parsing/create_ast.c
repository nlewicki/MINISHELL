/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:53:16 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/07 13:26:39 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*expr(int prec, t_list **token);

int get_precedence(t_token_type type)
{
    if (type == TOKEN_WORD || type == TOKEN_VARIABLE)
        return 0;
    if (type == TOKEN_COMMAND)
        return 1;
    if (type == TOKEN_PIPE)
        return 2;
    if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT ||
        type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HERE)
        return 3;
    return -1;
}

t_ast *create_ast_node(t_token_type type)
{
    t_ast *node = malloc(sizeof(t_ast));
    if (!node) return NULL;
    node->type = type;
    node->filename = NULL;
    node->heredoc = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void	create_node(t_token_type type, t_ast **node)
{
	*node = create_ast_node(type);
}


t_ast *nud(t_list **token)
{
    t_ast *node = NULL;
    t_token *curr_token = (t_token *)(*token)->content;
    if (curr_token->type == TOKEN_WORD || curr_token->type == TOKEN_COMMAND)
    {
        node = create_ast_node(curr_token->type);
        if (!node)
            return NULL;
        node->filename = curr_token->content;

        // Move to the next token
        *token = (*token)->next;
    }
    return node;
}

t_ast *led(t_ast *left, t_list **token)
{
    t_ast *node = NULL;
    int prec;

    t_token *curr_token = (t_token *)(*token)->content;
    prec = get_precedence(curr_token->type);  // Use get_hierarchy here

    if (prec > 0)
    {
        node = create_ast_node(curr_token->type);
        if (!node)
            return NULL;

        node->left = left;  // Left child is the previous expression
        node->right = NULL; // Right child will be parsed next

        // Move to the next token
        *token = (*token)->next;

        // For redirection operators, handle file names (right-hand side)
        if (prec == 3)  // Redirection precedence should be 3, not 2
        {
            t_token *next_token = (t_token *)(*token)->content;
            node->filename = next_token->content;
            *token = (*token)->next;
        }
        else  // For pipes or other operators
        {
            node->right = expr(prec, token);  // Parse the right-hand expression
            if (!node->right)
                return NULL;
        }
    }
    return node;
}


t_ast	*expr(int prec, t_list **token)
{
	t_ast	*left;

	left = nud(token);
	if (!left)
		return NULL;

	while (*token && get_precedence(((t_token *)(*token)->content)->type) > prec)
	{
		left = led(left, token);
		if (!left)
			return NULL;
	}
	return left;
}

t_ast	*parse(t_list **token)
{
	if (!token || !*token)
		return NULL;

	// Start parsing with the lowest precedence (0)
	return expr(0, token);
}

void handle_redirection(t_list **token, t_ast **node)
{
    t_token *curr_token = (t_token *)(*token)->content;
    if (curr_token->type == TOKEN_REDIR_IN || curr_token->type == TOKEN_REDIR_OUT
        || curr_token->type == TOKEN_REDIR_APPEND || curr_token->type == TOKEN_REDIR_HERE)
    {
        *node = create_ast_node(curr_token->type);
        t_token *next_token = (t_token *)(*token)->next->content;
        (*node)->filename = next_token->content; // Redirection target file

        // Move to the next token (filename)
        *token = (*token)->next;
    }
}
