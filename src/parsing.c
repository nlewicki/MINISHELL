/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:23:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/03 13:10:47 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_list *list);

int	g_signal = 0;

bool	isspecials(char c)
{
	char	*specials;

	specials = "<>|\'\"$";
	while (*specials)
	{
		if (c == *specials)
			return (true);
		specials++;
	}
	return (false);
}

void	trim_str(t_trim *trim, char *input)
{
	trim->i = 0;
	trim->j = 0;
	trim->is_space = false;
	trim->error = false;
	while (trim->i < trim->len)
	{
		if (isspecials(input[trim->i]))
			handle_specials(trim, input);
		else if (isspace(input[trim->i]))
		{
			if (!trim->is_space && trim->j > 0)
			{
				trim->result[trim->j++] = ' ';
				trim->is_space = true;
			}
		}
		else
		{
			trim->result[trim->j++] = input[trim->i];
			trim->is_space = false;
		}
		trim->i++;
	}
	trim->result[trim->j] = '\0';
}

char	*trim_whitespace(char *input)
{
	t_trim	trim;
	char	*new;

	trim.len = ft_strlen(input);
	trim.result = ft_calloc(sizeof(char), trim.len + 100);
	if (!trim.result)
	{
		return (NULL);
	}
	trim_str(&trim, input);
	if (trim.error == true)
	{
		free(trim.result);
		return (NULL);
	}
	printf("result: %s\n", trim.result);
	new = ft_strtrim(trim.result, " \t\f\n\v\r");
	if (!new)
		return (NULL);
	printf("trimmed: %s\n", new);
	return (new);
}

void free_token(void *content)
{
	t_token *token;

	token = (t_token *)content;
	free(token->content);
	free(token);
}

int	parse_input(char *input)
{
	char	*new;
	char	**tokens;

	printf("input: %s\n", input);
	new = trim_whitespace(input);
	if (!new)
		return (1);
	tokens = split_space_quotes(new);
	free(new);
	if (!tokens)
		return (1);

	size_t	i; // only debugg
	t_token *strct;
	t_list *list = NULL;
	i = 0;
	while (tokens[i])
	{
		printf("Token %zu:%s\n", i, tokens[i]);
		strct = malloc(sizeof(t_token));
		if (!strct)
			return (1);
		fill_struct(strct ,tokens[i]);
		t_list *new = ft_lstnew(strct);
		ft_lstadd_back(&list, new);
		i++;
	} // end debugg

	// check linked list
	print_token_list(list);

	free_token_array(tokens);
	ft_lstclear(&list, free_token);
	return (0);
}


// ANSI color codes
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
		else if (token->type == TOKEN_VARIABLE)
			printf("Token: VARIABLE (%s)\n", token->content);
		else if (token->type == TOKEN_COMMAND)
			printf("Token: COMMAND (%s)\n", token->content);

		// Print previous content
		if (list->prev)
		{
			t_token *prev_token = (t_token *)list->prev->content;
			printf(COLOR_PREV "\tPrev content: ");
			if (prev_token->type == TOKEN_WORD)
				printf("WORD (%s)\n", prev_token->content);
			else if (prev_token->type == TOKEN_PIPE)
				printf("PIPE\n");
			else if (prev_token->type == TOKEN_REDIR_IN)
				printf("REDIR IN\n");
			else if (prev_token->type == TOKEN_REDIR_OUT)
				printf("REDIR OUT\n");
			else if (prev_token->type == TOKEN_REDIR_APPEND)
				printf("REDIR APPEND\n");
			else if (prev_token->type == TOKEN_REDIR_HERE)
				printf("HEREDOC\n");
			else if (prev_token->type == TOKEN_VARIABLE)
				printf("VARIABLE\n");
			else if (prev_token->type == TOKEN_COMMAND)
				printf("COMMAND\n");
		}
		else
		{
			printf(COLOR_PREV "\tPrev content: NULL\n" COLOR_RESET);
		}

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
			else if (next_token->type == TOKEN_VARIABLE)
				printf("VARIABLE\n");
			else if (next_token->type == TOKEN_COMMAND)
				printf("COMMAND\n");
		}
		else
		{
			printf(COLOR_NEXT "\tNext content: NULL\n" COLOR_RESET);
		}

			// Reset color to default after each node
		printf(COLOR_RESET);
		list = list->next;
		i++;
	}
}
