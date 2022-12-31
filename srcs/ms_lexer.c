/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:35:40 by zah               #+#    #+#             */
/*   Updated: 2022/12/30 16:34:45 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>

static t_lexer	*lexer_init(char *input);
static void		interpret_split(char *current, int length, t_main *main);

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
	char	*current;

	lexer = lexer_init(input);

	while (*lexer->current != '\0')
	{
		if (ms_get_split_length(lexer) == -1)
		{
			printf ("Quote not properly enclosed\n");
			break ;
		}
		interpret_split(lexer->current, ms_get_split_length(lexer), main);
		lexer->current += ms_get_split_length(lexer);
	}
	free (lexer);
}

/**
 * @brief Intepret the splitted string. First, create a new string 
 * based on split length. Then, check whether the string contain $ sign
 * If contain, create a new string that store the expanded value.
 * Finally, create a new string that join both and convert this to token.
 * The quote is preserved throughout this process
 */
static void	interpret_split(char *current, int length, t_main *main)
{
	int		i;
	char	*base;
	char 	*expand;

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
	printf("Original :%s\n", base);
	expand = ms_expander(base, main);
	printf("Expand :%s\n", expand);
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
