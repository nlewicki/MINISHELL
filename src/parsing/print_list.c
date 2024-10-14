/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:34:16 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/10 12:11:40 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// check linked list
#define COLOR_RESET "\033[0m"
#define COLOR_PREV "\033[34m" // Blue for previous
#define COLOR_NEXT "\033[32m" // Green for next

void	print_token_list(t_list *list)
{
	t_token *token;
	size_t	i = 0;

	while (list)
	{
		token = (t_token *)list->content;
		printf("Node %zu: ", i);
		if (token->type == TOKEN_PIPE)
			printf("Token: PIPE (%s)\n", token->content);
		else if (token->type == TOKEN_REDIR_IN)
			printf("Token: REDIR IN (%s)\n", token->content);
		else if (token->type == TOKEN_REDIR_OUT)
			printf("Token: REDIR OUT (%s)\n", token->content);
		else if (token->type == TOKEN_REDIR_APPEND)
			printf("Token: REDIR APPEND (%s)\n", token->content);
		else if (token->type == TOKEN_REDIR_HERE)
			printf("Token: HEREDOC (%s)\n", token->content);
		else if (token->type == TOKEN_WORD)
			printf("Token: WORD (%s)\n", token->content);

		// Print next content
		if (list->next)
		{
			t_token *next_token = (t_token *)list->next->content;
			printf(COLOR_NEXT "\tNext content: ");
			if (next_token->type == TOKEN_WORD)
				printf("WORD (%s)\n", next_token->content);
			else if (next_token->type == TOKEN_PIPE)
				printf("PIPE\n");
			else if (next_token->type == TOKEN_REDIR_IN)
				printf("REDIR IN\n");
			else if (next_token->type == TOKEN_REDIR_OUT)
				printf("REDIR OUT\n");
			else if (next_token->type == TOKEN_REDIR_APPEND)
				printf("REDIR APPEND\n");
			else if (next_token->type == TOKEN_REDIR_HERE)
				printf("HEREDOC\n");
		}
		else
		{
			printf(COLOR_NEXT "\tNext content: NULL\n" COLOR_RESET);
		}

		printf(COLOR_RESET);
		list = list->next;
		i++;
	}
	printf("\n\n");
}
