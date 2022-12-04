/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:26:19 by zah               #+#    #+#             */
/*   Updated: 2022/12/04 17:23:58 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_enclosed_length(char *str, char quote);
static char	*trim_input(char *str, t_dlist **token_list);

/**
 * @brief Main function of lexer, turn the string to smaller token
 * and sent it to parser.
 * @param input The line return from readline
 */
void	ms_process_input(char *input)
{
	char	*remain;
	t_dlist	*head;

	remain = trim_input(input, &head);
	while (remain != NULL)
	{
		remain = trim_input(remain, &head);
	}
	print_token_list(&head);
}

/**
 * @brief Process the input until a separator is met.
 * Return the remaining string after separator.
 * Separator include space, tab, enclosed single and double quote
 * @param str The string to trim
 * @param token_list Address to the token linked list
 * @return The remaining string, NULL if end is reached
 */
static char	*trim_input(char *str, t_dlist **token_list)
{
	int	i;

	while (*str == ' ' || *str == '\t')
		str ++;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			break ;
		else if (str[i] == 34 || str[i] == 39)
		{
			i = get_enclosed_length(str, str[i]);
			break ;
		}
		i ++;
	}
	if (i == -1)
		ms_error_exit("Quote is unclosed");
	ms_tokenize(str, i, token_list);
	if (str[i] == '\0')
		return (NULL);
	else
		return (str + i);
}

/**
 * @brief Check whether a string open with quote is properly enclosed.
 * if yes, get the length of enclosed sting, inclusive of both open and end quote
 * @param str The input string
 * @param quote The character used to open the quote
 * @return int The length of enclosed quote. -1 if not enclosed
 */
static	int	get_enclosed_length(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			return (i + 1);
		i ++;
	}
	return (-1);
}
