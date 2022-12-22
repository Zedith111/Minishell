/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:38:50 by zah               #+#    #+#             */
/*   Updated: 2022/12/22 15:08:14 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_sep(char c);
static int	check_file_type(char *str);

/**
 * @brief Get the length of the split string when encounter a separator.
 * When encounter quote, check the length of the enclosed quote(inclusive).
 * If quote is not properly enclosed, return -1;
 * When encounter < or >, check if the next character is the same.
 * If yes, set the split length to two.
 * When encounter space, tab and |, just break
 */
int	get_split_length(t_lexer *lexer)
{
	int	i;

	while (is_sep(*lexer->current) == 3)
		lexer->current ++;
	i = 0;
	while (lexer->current[i] != '\0')
	{
		if (is_sep(lexer->current[i]) == 1)
		{
			if (ms_check_enclosed_length(lexer->current, lexer->current[i]) == -1)
				return (-1);
			i += ms_check_enclosed_length(lexer->current, lexer->current[i]);
		}
		if (is_sep(lexer->current[i]) == 2)
		{
			i = check_file_type(lexer->current);
			break;
		}
		if (is_sep(lexer->current[i]) == 3)
			break;
		else
			i++;
	}
	return (i);
}

/**
 * @brief Check the length of the enclosed quote.
 * Length is inclusive of open and close quote.
 * Return -1 if quote is not enclosed
 */
int	ms_check_enclosed_length(char *str, char quote)
{
	int		i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			return (i + 1);
		i ++;
	}
	return (-1);
}

/**
 * @brief Check whether a character is a separator. Return 0
 * if not, or the respective number
 * @return 1 for single & double quote, 2 for > & <, 3 for space, tab, and |
 */
static int	is_sep(char c)
{
	if (c == 34 || c == 39)
		return (1);
	if (c == '<' || c == '>')
		return (2);
	if (c == ' ' || c == '\t' || c == '|')
		return (3);
	return (0);
}

//Token.c interpret the split length and create token
//expander expand
static int	check_file_type(char *str)
{
	char	first;

	first = str[0];
	if (str[1] == first)
		return (2);
	return (1);
}