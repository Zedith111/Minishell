/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:52:24 by zah               #+#    #+#             */
/*   Updated: 2022/12/04 19:21:51 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_token_type(char *str);
static t_dlist		*create_word_token(char *str, int stop);
static t_dlist		*create_spec_token(char *str, int stop, t_token *token);

/**
 * @brief Transform the string into individual token that store both type and 
 * value. Also separate the operator out. |wc will be separate to | and "wc".
 * Add the newly create token to the token list
 * @param str The input string
 * @param stop The stopping position
 * @param token_list Address to the token linked list
 */
void	ms_tokenize(char *str, int stop, t_dlist **token_list)
{
	t_token			*token;
	t_token_type	type;

	type = get_token_type(str);
	if (type == TOKEN_WORD)
		ft_dlist_addback(token_list, create_word_token(str, stop));
	else
	{
		token = malloc (sizeof (t_token));
		token->type = type;
		ft_dlist_addback(token_list, create_spec_token(str, stop, token));
	}
	//expand
}

/**
 * @brief Check the first character and return the respective token type
 * @param str The string to check
 * @return The respective token_type
 */
static t_token_type	get_token_type(char *str)
{
	if (*str == 39 || *str == 34)
		return (TOKEN_WORD);
	else if (*str == '|')
		return (TOKEN_PIPE);
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (TOKEN_AOUT);
		return (TOKEN_OUT);
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (TOKEN_AIN);
		return (TOKEN_IN);
	}
	return (TOKEN_WORD);
}

static t_dlist	*create_word_token(char *str, int stop)
{
	char	*value;
	int		i;
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = TOKEN_WORD;
	value = malloc(stop + 1);
	i = 0;
	while (i < stop)
	{
		value[i] = str[i];
		i ++;
	}
	value[i] = '\0';
	if (ms_is_empty_string(value))
	{
		free (value);
		free (token);
		return (NULL);
	}
	token->value = value;
	return (ft_dlist_new(token));
}

static t_dlist	*create_spec_token(char *str, int stop, t_token *token)
{
	int		length;
	char	*value;
	int		i;
	t_dlist	*node;

	length = 1;
	if (token->type == TOKEN_AIN || token->type == TOKEN_AOUT)
		length = 2;
	value = malloc(length + 1);
	i = 0;
	while (i < length)
	{
		value[i] = str[i];
		i ++;
	}
	value[i] = '\0';
	token->value = value;
	node = ft_dlist_new(token);
	if (stop != length)
	{
		ft_dlist_addback(&node, create_word_token(str + length, stop - length));
	}
	return (node);
}
