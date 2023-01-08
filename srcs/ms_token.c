/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:44:54 by zah               #+#    #+#             */
/*   Updated: 2023/01/08 15:37:30 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_token_type(char *str);
static t_dlist		*interpret_word(char *str);
static int			tokenizer_advance(char *str);

/**
 * @brief Return a token node or a list of token node when input a string.
 * First check for first character of the string, if is special character,
 * just create the respective type of token. If is other than that, create
 * a node or a list of word token.
 */
t_dlist	*ms_tokenized(char *str)
{
	t_dlist	*rtn;
	t_token	*token;

	if (*str == '<' || *str == '>' || *str == '|')
	{
		token = (t_token *)malloc (sizeof(t_token));
		token->type = get_token_type(str);
		token->value = NULL;
		rtn = ms_dlist_new(token);
	}
	else if (*str == '\0')
		rtn = ms_create_word_token("");
	else
		rtn = interpret_word(str);
	return (rtn);
}

/**
 * @brief Return the respective token type based on operator
 */
static t_token_type get_token_type(char *str)
{
	if (*str == '|')
		return (TOKEN_PIPE);
	if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (TOKEN_AIN);
		return (TOKEN_IN);
	}
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (TOKEN_AOUT);
		return (TOKEN_OUT);
	}
	return (TOKEN_ERR);
}

/**
 * @brief Return a single node or a list of word token based on
 * the string. When encouter space outside quote, the current intepreted
 * string is convert to one token, and the string after the space  
 * is interpret as new token. When encounter a quote, the opening
 * and closing quote is trimmed and is joined with previous result
 */
static t_dlist	*interpret_word(char *str)
{
	t_dlist	*rtn;
	int		i;
	char	*temp;
	char	*result;

	i = 0;
	result = ms_create_empty_string();
	rtn = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			result = ms_tokenize_space(result, &rtn);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			temp = ms_token_trim(str + i);
			result = ms_strjoin_free(result, temp);
		}
		else
			result = ms_strjoin_free(result,
					ms_strdup_length(str + i, tokenizer_advance(str + i)));
		i += tokenizer_advance(str + i);
	}
	ms_dlist_addback(&rtn, ms_create_word_token(result));
	free (result);
	return (rtn);
}

/**
 * @brief Return the length that the tokenizer need to advance.
 * Check for the first character in the string, If is quote, then
 * return the enclosed length. If is space, move until it meet the 
 * next space. Or else, breaks when it meet a space or quote
 * and return the length.
 */
static int	tokenizer_advance(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"' || str[i] == '\'')
		return (ms_check_enclosed_length(str));
	if (str[i] == ' ' || str[i] == '\t')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i ++;
		return (i);
	}
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\"' || str[i] == '\'')
			break ;
		else
			i ++;
	}
	return (i);
}
