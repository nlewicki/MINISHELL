/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:53:33 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/16 10:07:43 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	t_token *token;

	token = (t_token *)content;
	free(token->content);
	free(token);
}

int	create_linked_list(char **tokens, t_list **list)
{
	write(1, "\ncreate_linked_list\n", 20);
	size_t	i;
	t_token	*strct;

	i = 0;
	while (tokens[i])
	{
		strct = malloc(sizeof(t_token));
		if (!strct)
			return (1);
		fill_struct(strct, tokens[i]);
		t_list *new = ft_lstnew(strct);
		if (!new)
		{
			free(strct);
			return (1);
		}
		ft_lstadd_back(list, new);
		i++;
	}
	return (0);
}
