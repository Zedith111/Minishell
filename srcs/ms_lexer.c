/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:35:40 by zah               #+#    #+#             */
/*   Updated: 2022/12/22 14:41:36 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

static t_lexer	*lexer_init(char *input);


void	interpret_split(char *current, int length);

/**
 * @brief Main function of lexer, turn the line into smaller token
 * and store it in linked ist. The lexer perform several step.
 * Example : This is a "combined"string with" space" |>'outfile' | ec"ho hi" $USER
 * 1) Split the string based on space and operator (<,>,|). Anything inside quote is been reserved
 * 		This, is, a, "combined"string, with" space", |, >, 'outfile', |, ec"ho hi", $USER
 * 2) Expand the variable inside double quote or start with $ and join it back to token
 * 		This, is, a, combinedstring, with space, |, >, outfile, | echo hi, zah
 * 3) Put this into a token list, which contain both the type and value
 * @param input The line return from readline
 */
void	ms_process_input(char *input, t_main *main)
{
	t_lexer	*lexer;
	// t_token	*token;
	// t_dlist	*token_list;
	char	*current;

	lexer = lexer_init(input);

	// while (*lexer->current != '\0')
	// {
	// 	printf ("Length :%d\n", get_split_length(lexer));
	// 	// printf("Before :%s\n", lexer->current);
	// 	interpret_split(lexer->current, get_split_length(lexer));
	// 	lexer->current += get_split_length(lexer);
	// }
	printf("%d\n",get_split_length(lexer));
	// token = lexer_advance(lexer);
	// token_list = NULL;
	// while (token->type != TOKEN_END)
	// {
	// 	if (token->type == TOKEN_ERR)
	// 	{
	// 		ms_dlist_clear(&token_list, &ms_free_token);
	// 		free (lexer);
	// 		free (token);
	// 		return ;
	// 	}
	// 	ms_dlist_addback(&token_list, ms_dlist_new(token));
	// 	token = lexer_advance(lexer);
	// }
	// ms_trim_list(token_list);
	// ms_expand_list(token_list, main);
	// ms_parse_input(token_list, main);
	// free (lexer);
	// free (token);
}


void	interpret_split(char *current, int length)
{
	int i = 0;
	char *result = malloc (sizeof(char) * length +1);

	if (length == 0)
	{
		printf("empty\n");
		return ;
	}

	while (i < length)
	{
		result[i] = current[i];
		i ++;
	}
	result[i]= '\0';
	printf("Result :%s\n", result);
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
// static t_token	*lexer_advance(t_lexer *lexer)
// {
// 	while (ms_is_sep(*lexer->current) == 4)
// 		lexer->current ++;
// 	if (*lexer->current == '\0')
// 		return (ms_create_token(TOKEN_END, NULL));
// 	if (ms_is_sep(*lexer->current) == 1)
// 		return (ms_create_quote_token(lexer));
// 	if (ms_is_sep(*lexer->current) == 2 || ms_is_sep(*lexer->current) == 3)
// 		return (ms_create_operator_token(lexer));
// 	else
// 		return (ms_create_word_token(lexer));
// }


