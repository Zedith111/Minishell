/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:35:40 by zah               #+#    #+#             */
/*   Updated: 2022/12/12 15:10:12 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

static t_lexer	*lexer_init(char *input);
static t_token	*lexer_advance(t_lexer *lexer);

/**
 * @brief Main function of lexer, turn the line into smaller token
 * and add it to linked ist
 * @param input The line return from readline
 */
void	ms_process_input(char *input)
{
	t_lexer	*lexer;
	t_token	*token;
	t_dlist	*head;

	lexer = lexer_init(input);
	token = lexer_advance(lexer);
	head = NULL;
	while (token->type != TOKEN_END)
	{
		if (token->type == TOKEN_ERR)
		{
			//Free list
			ms_error_exit("Quote unclosed");
		}
		ms_dlist_addback(&head, ms_dlist_new(token));
		token = lexer_advance(lexer);
	}
	//Pass to parser
	print_token_list(&head);
	//free token list at parser
	ms_dlist_clear(&head, &ms_token_free);
	free (lexer);
	free (token);
}

/**
 * @brief Initialize and return the lexer struct 
 * @param input The input string pass from readline
 */
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

/**
 * @brief Free the token struct and the value in it
 */
void	ms_token_free(void *token)
{
	t_token	*target;

	target = (t_token *)token;
	free(target->value);
	free(target);
}
