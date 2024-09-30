/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:37:06 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/30 12:37:43 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node *create_command_node(char **command)
{
    t_ast_node *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = NODE_COMMAND;
    node->command = command;
    node->left = NULL;
    node->right = NULL;
    node->filename = NULL;
    node->redir_type = 0;
    return (node);
}

t_ast_node	*create_pipeline_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPELINE;
	node->left = left;
	node->right = right;
	node->command = NULL;
	node->filename = NULL;
	node->redir_type = 0;
	return (node);
}

t_ast_node	*create_redirection_node(t_ast_node *command, char *filename, int redir_type)
{
	t_ast_node *node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_REDIRECTION;
	node->left = command;       // The command that gets redirected
	node->filename = filename;  // The file for redirection
	node->redir_type = redir_type; // Type of redirection (INPUT, OUTPUT, APPEND)
	node->command = NULL;
	node->right = NULL;
	return (node);
}
