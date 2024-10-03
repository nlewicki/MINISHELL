/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:23:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/03 12:54:05 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

typedef struct s_trim
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len;
	bool	is_space;
	bool	error;
}			t_trim;

void	handle_history(char *input)
{
	if (g_signal == 0)
	{
		if (ft_strlen(input) > 0)
			add_history(input);
		else
			free(input);
	}
}

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

void	handle_operator(t_trim *trim, char *input)
{
	if (trim->j > 0 && !isspace(trim->result[trim->j - 1]))
		trim->result[trim->j++] = ' ';
	trim->result[trim->j++] = input[trim->i];
	if ((input[trim->i] == '<' && input[trim->i + 1] == '<')
		|| (input[trim->i] == '>' && input[trim->i + 1] == '>'))
		trim->result[trim->j++] = input[++trim->i];
	if (input[trim->i] != '$')
		trim->result[trim->j++] = ' ';
}

void	handle_quotes(t_trim *trim, char *input)
{
	char	quote;

	if (trim->j > 0 && (!isspace(trim->result[trim->j - 1])))
		trim->result[trim->j++] = ' ';
	quote = input[trim->i];
	trim->result[trim->j++] = input[trim->i++];
	while ((input[trim->i] != '\0') && (input[trim->i] != quote))
		trim->result[trim->j++] = input[trim->i++];
	if (input[trim->i] == quote)
	{
		trim->result[trim->j++] = input[trim->i];
		trim->result[trim->j++] = ' ';
	}
	else
	{
		printf("Missing closing quote\n");
		trim->error = true;
	}
}

void	handle_specials(t_trim *trim, char *input)
{
	char	tmp;

	if ((input[trim->i] == '\'') || (input[trim->i] == '\"'))
	{
		handle_quotes(trim, input);
		trim->is_space = true;
	}
	else if (input[trim->i] == '|' || input[trim->i] == '>'
		|| input[trim->i] == '<' || input[trim->i] == '$')
	{
		tmp = input[trim->i];
		handle_operator(trim, input);
		if (tmp == '$')
			trim->is_space = false;
		else
			trim->is_space = true;
	}
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

// debugg only fucniton
void	print_token_list(t_list *list)
{
	t_token	*token;
	size_t	i;
	t_token	*prev_token;
	t_token	*next_token;

	i = 0;
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
		if (list->prev)
		{
			prev_token = (t_token *)list->prev->content;
			printf("\tPrev content: ");
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
		}
		else
		{
			printf("\tPrev content: NULL\n");
		}
		if (list->next)
		{
			next_token = (t_token *)list->next->content;
			printf("\tNext content: ");
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
			printf("\tNext content: NULL\n");
		}
		list = list->next;
		i++;
	}
}

int	parse_input(char *input)
{
	char	*new;
	char	**tokens;
	t_token	*strct;
	t_list	*list;
	t_list	*new;

	printf("input: %s\n", input);
	new = trim_whitespace(input);
	if (!new)
		return (1);
	tokens = split_space_quotes(new);
	free(new);
	if (!tokens)
		return (1);
	size_t i; // only debugg
	list = NULL;
	i = 0;
	while (tokens[i])
	{
		printf("Token %zu:%s\n", i, tokens[i]);
		strct = malloc(sizeof(t_token));
		if (!strct)
			return (1);
		fill_struct(strct, tokens[i]);
		new = ft_lstnew(strct);
		ft_lstadd_back(&list, new);
		i++;
	} // end debugg
	// check linked list
	print_token_list(list);
	free_token_array(tokens);
	return (0);
}
