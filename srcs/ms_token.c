/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:44:54 by zah               #+#    #+#             */
/*   Updated: 2022/12/14 16:10:51 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check whether a string start with quote is properly end
 * @param str The string to check for
 * @param open The quote character
 * @return The length of enclosed string, -1 if not enclosed properly
 */
static int	check_enclosed(char *str, char open)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == open)
			return (i + 1);
		i ++;
	}
	return (-1);
}

/**
 * @brief Create and return a token based on type and value
 */
t_token	*ms_create_token(t_token_type type, char *value)
{
	t_token	*rtn;

	rtn = malloc(sizeof(t_token));
	rtn->type = type;
	rtn->value = value;
	return (rtn);
}

t_token	*ms_create_quote_token(t_lexer *lexer)
{
	char	sep;
	char	*value;
	int		i;

	sep = *lexer->current;
	i = check_enclosed(lexer->current, sep);
	if (i == -1)
		return (ms_create_token(TOKEN_ERR, NULL));
	value = ft_substr(lexer->current, 0, i);
	lexer->current += i;
	return (ms_create_token(TOKEN_QUOTE, value));
}

t_token	*ms_create_word_token(t_lexer *lexer)
{
	int		i;
	char	*value;

	i = 0;
	while (lexer->current[i] != '\0' && ms_is_sep(lexer->current[i]) == 0)
		i++;
	value = ft_substr(lexer->current, 0, i);
	if (ms_is_empty_string(value))
	{
		value = malloc(1);
		return (ms_create_token(TOKEN_END, value));
	}
		
	lexer->current += i;
	return (ms_create_token(TOKEN_WORD, value));
}

t_token	*ms_create_operator_token(t_lexer *lexer)
{
	if (*lexer->current == '|')
	{
		lexer->current += 1;
		return (ms_create_token(TOKEN_PIPE, NULL));
	}
	else if (*lexer->current == '>')
	{
		lexer->current += 1;
		if (*lexer->current == '>')
		{
			lexer->current += 1;
			return (ms_create_token(TOKEN_AOUT, NULL));
		}
		return (ms_create_token(TOKEN_OUT, NULL));
	}
	else
	{
		lexer->current += 1;
		if (*lexer->current == '<')
		{
			lexer->current += 1;
			return (ms_create_token(TOKEN_AOUT, NULL));
		}
		return (ms_create_token(TOKEN_OUT, NULL));
	}
}
