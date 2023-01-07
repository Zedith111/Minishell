/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:35:40 by zah               #+#    #+#             */
/*   Updated: 2023/01/07 22:05:07 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

static t_lexer	*lexer_init(char *input);
static void		interpret_split(char *current, int length,
					t_dlist *token_list, t_main *main);

/**
 * @brief Main function of lexer, turn the line into smaller token
 * and store it in linked ist. The lexer perform several step.
 * 1) Split the string based on space and operator (<,>,|).
 * 	  Anything inside quote is been preserved
 * 2) Expand the variable inside double quote or start with $ and join it back
 * 3) Put this into a token list, which contain both the type and value
 * @param input The line return from readline
 */
void	ms_process_input(char *input, t_main *main)
{
	t_lexer	*lexer;
	t_dlist	*token_list;

	lexer = lexer_init(input);
	token_list = NULL;
	while (*lexer->current != '\0')
	{
		if (ms_get_split_length(lexer) == -1)
		{
			printf ("Quote not properly enclosed\n");
			break ;
		}
		interpret_split(lexer->current, ms_get_split_length(lexer),
			token_list, main);
		lexer->current += ms_get_split_length(lexer);
	}
	free (lexer);
}

/**
 * @brief Intepret the splitted string. First, duplicate the string
 * based on split length. Then expand the string out. The quote is 
 * still preserved in this stage. Lastly, convert the expanded string 
 * to tokens. The quote is trimmed out in this stage.
 */
static void	interpret_split(char *current, int length,
					t_dlist *token_list, t_main *main)
{
	int		i;
	char	*base;
	char	*expand;

	i = 0;
	if (length == 0)
		return ;
	base = malloc (length + 1);
	while (i < length)
	{
		base[i] = current[i];
		i ++;
	}
	base[i] = '\0';
	expand = ms_expander(base, main);
	ms_dlist_addback(&token_list, ms_tokenized(expand));
	print_token_list(&token_list);
	free(expand);
	free (base);
}

static t_lexer	*lexer_init(char *input)
{
	t_lexer	*rtn;

	rtn = malloc (sizeof(t_lexer));
	rtn->input = input;
	rtn->current = input;
	return (rtn);
}
