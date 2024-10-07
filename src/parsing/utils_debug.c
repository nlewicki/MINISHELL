/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:07:32 by tecker            #+#    #+#             */
/*   Updated: 2024/10/07 13:30:39 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *node_type_to_string(t_token_type type)
{
    switch (type)
    {
        case TOKEN_COMMAND:
            return "TOKEN_COMMAND";
        case TOKEN_PIPE:
            return "TOKEN_PIPE";
        case TOKEN_REDIR_IN:
            return "TOKEN_REDIR_IN";
        case TOKEN_REDIR_OUT:
            return "TOKEN_REDIR_OUT";
        case TOKEN_REDIR_APPEND:
            return "TOKEN_REDIR_APPEND";
        case TOKEN_REDIR_HERE:
            return "TOKEN_REDIR_HERE";
        case TOKEN_VARIABLE:
            return "TOKEN_VARIABLE";
        case TOKEN_WORD:
            return "TOKEN_WORD";
        default:
            return "UNKNOWN";
    }
}

// Helper function to print the AST recursively
void print_ast_helper(t_ast *node, char *prefix)
{
    if (!node)
        return;

    printf("%sNode Type: %s\n", prefix, node_type_to_string(node->type));
    if (node->filename)
    {
        printf("%sFilename: %s\n", prefix, node->filename);
    }
    if (node->heredoc)
    {
        printf("%sHeredoc: %s\n", prefix, node->heredoc);
    }

    // Recursively print left and right children
    if (node->left)
    {
        printf("%sLeft Child:\n", prefix);
        print_ast_helper(node->left, strcat(strcat(strdup(prefix), "  "), "  "));
    }
    if (node->right)
    {
        printf("%sRight Child:\n", prefix);
        print_ast_helper(node->right, strcat(strcat(strdup(prefix), "  "), "  "));
    }
}

// Main function to print the AST
void print_ast(t_ast *node)
{
    print_ast_helper(node, "");
    printf("\n");
}

// Converts token type to a string for debugging
const char *token_type_to_string(t_token_type type)
{
    switch (type)
    {
        case TOKEN_PIPE:
            return "TOKEN_PIPE";
        case TOKEN_REDIR_IN:
            return "TOKEN_REDIR_IN";
        case TOKEN_REDIR_OUT:
            return "TOKEN_REDIR_OUT";
        case TOKEN_REDIR_APPEND:
            return "TOKEN_REDIR_APPEND";
        case TOKEN_REDIR_HERE:
            return "TOKEN_REDIR_HERE";
        case TOKEN_VARIABLE:
            return "TOKEN_VARIABLE";
        case TOKEN_WORD:
            return "TOKEN_WORD";
        case TOKEN_COMMAND:
            return "TOKEN_COMMAND";
        default:
            return "UNKNOWN";
    }
}

// Function to print all tokens in the linked list
void print_token_liste(t_list *list)
{
    int i = 1;
    t_list *current = list;

    while (current)
    {
        t_token *token = (t_token *)current->content; // Access the token from the list node
        printf("Token %d:\n", i);
        printf("  Type: %s\n", token_type_to_string(token->type));
        printf("  Value: %s\n", token->content); // Adjusted to use 'content' based on your definition
        current = current->next; // Move to the next token in the list
        i++;
    }
}
