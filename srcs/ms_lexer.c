/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:26:19 by zah               #+#    #+#             */
/*   Updated: 2022/12/01 15:31:04 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_enclosed_length(char *str, char quote);
static char	*trim_input(char *str);
static void	tokenize(char *str, int stop);

/**
 * @brief Main function of lexer, turn the string to smaller token
 * 
 * @param input The line return from readline
 */
void	ms_process_input(char *input)
{
	
}

/**
 * @brief Process the input until a separator is met.
 * Return the remaining string after separator.
 * Separator include space, tab, enclosed single and double quote
 * @param str The string to trim
 * @return char* The remaining string, NULL if end is reached
 */
static char	*trim_input(char *str)
{
	int	i;

	while (*str == ' ' || *str == '\t')
		str ++;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i])
	}
	
}

/**
 * @brief Check whether a string open with quote is properly enclosed
 * 
 * @param str The string to 
 * @param quote 
 * @return int The length of enclosed quote. -1 if not enclosed
 */
static int	get_enclosed_length(char *str, char quote)
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

static void	tokenize(char *str, int stop)
{
	
}