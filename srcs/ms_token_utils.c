/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:22:27 by zah               #+#    #+#             */
/*   Updated: 2023/01/08 13:36:49 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a word token based on the content
 */
t_dlist	*ms_create_word_token(char *content)
{
	t_dlist	*rtn;
	t_token	*token;

	token = (t_token *)malloc (sizeof(t_token));
	token->type = TOKEN_WORD;
	token->value = ft_strdup(content);
	rtn = ms_dlist_new(token);
	return (rtn);
}

char	*ms_token_trim(char *str)
{
	char	*quote;
	char	*temp;
	char	*rtn;

	quote = malloc(2);
	quote[0] = *str;
	quote[1] = '\0';
	temp = ms_strdup_length(str, ms_check_enclosed_length(str));
	rtn = ft_strtrim(temp, quote);
	free (temp);
	free (quote);
	return (rtn);
}

char	*ms_tokenize_space(char *current, t_dlist **list)
{
	ms_dlist_addback(list, ms_create_word_token(current));
	free(current);
	return (ms_create_empty_string());
}