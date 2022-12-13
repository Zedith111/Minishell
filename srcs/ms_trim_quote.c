/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_trim_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:44:05 by zah               #+#    #+#             */
/*   Updated: 2022/12/13 20:14:22 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trim_token(void *content);

/**
 * @brief Go through the linked list and trim out " and '.
 * If " detected, trim the token and change the token type to
 * word which will be further expanded. If ' detected, trim the token only
 */
void	ms_trim_list(t_dlist *head)
{
	t_dlist	*current;

	current = head;
	while (current != NULL)
	{
		trim_token(current->content);
		current = current->next;
	}
}

static void	trim_token(void *content)
{
	t_token	*token;
	char	*trim_set;
	char	*temp;

	token = (t_token *)content;
	trim_set = "\"\'";
	if (token->type == TOKEN_QUOTE)
	{
		temp = token->value;
		if (token->value[0] == '\"')
		{
			token->type = TOKEN_WORD;
			token->value = ft_strtrim(token->value, trim_set);
		}
		else if (token->value[0] == '\'')
			token->value = ft_strtrim(token->value, trim_set);
		free (temp);
	}
}
