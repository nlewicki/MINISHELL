/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:53:16 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/07 12:18:32 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_hierarchy(t_token_type type)
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

t_ast *create_ast_node(t_token_type type, char *content)
{
    t_ast *node = malloc(sizeof(t_ast));
    if (!node) return NULL;

    node->type = type;
    node->args = NULL;
    node->filename = NULL;
    node->heredoc = NULL;
    node->left = NULL;
    node->right = NULL;

}

t_ast *parse_token(t_list **tokens)
{

}

t_ast *build_ast(t_list **list, t_ast **ast)
{
    
}
