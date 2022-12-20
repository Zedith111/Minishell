/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:35:40 by zah               #+#    #+#             */
/*   Updated: 2022/12/20 18:04:46 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

static t_lexer	*lexer_init(char *input);
static t_token	*lexer_advance(t_lexer *lexer);

/**
 * @brief Main function of lexer, turn the line into smaller token
 * and store it in linked ist
 * @param input The line return from readline
 */
void	ms_process_input(char *input, t_main *main)
{
	t_lexer	*lexer;
	t_token	*token;
	t_dlist	*token_list;

	lexer = lexer_init(input);
	token = lexer_advance(lexer);
	token_list = NULL;
	while (token->type != TOKEN_END)
	{
		if (token->type == TOKEN_ERR)
		{
			ms_dlist_clear(&token_list, &ms_free_token);
			free (lexer);
			free (token);
			return ;
		}
		ms_dlist_addback(&token_list, ms_dlist_new(token));
		token = lexer_advance(lexer);
	}
	ms_trim_list(token_list);
	ms_expand_list(token_list, main);
	ms_parse_input(token_list, main);
	free (lexer);
	free (token);
}

static t_lexer	*lexer_init(char *input)
{
	t_lexer	*rtn;

	rtn = malloc (sizeof(t_lexer));
	rtn->input = input;
	rtn->current = input;
	return (rtn);
}

/**
 * @brief Read through the line and producing indiviudal token.
 * Do this by reading through lexer, stop when the character is a separator
 * and create token based on type of separator
 * @return The token created
 */
static t_token	*lexer_advance(t_lexer *lexer)
{
	while (ms_is_sep(*lexer->current) == 4)
		lexer->current ++;
	if (*lexer->current == '\0')
		return (ms_create_token(TOKEN_END, NULL));
	if (ms_is_sep(*lexer->current) == 1)
		return (ms_create_quote_token(lexer));
	if (ms_is_sep(*lexer->current) == 2 || ms_is_sep(*lexer->current) == 3)
		return (ms_create_operator_token(lexer));
	else
		return (ms_create_word_token(lexer));
}

/**
 * @brief Check whether a character is separator
 * Return 0 if not, or the respective number
 * @return 1 for single & double quote, 2 for |, 3 for < and >.
 * 4 for space and tab , 0 for normal character
 */
int	ms_is_sep(char c)
{
	if (c == 34 || c == 39)
		return (1);
	if (c == '|')
		return (2);
	if (c == '<' || c == '>')
		return (3);
	if (c == ' ' || c == '\t')
		return (4);
	return (0);
}
