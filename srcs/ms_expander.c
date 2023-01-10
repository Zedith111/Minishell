/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:36:09 by zah               #+#    #+#             */
/*   Updated: 2023/01/10 17:34:41 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expander_interpret(char *str, int length, t_main *main);

/**
 * @brief Take a string as input, expand all variable inisde.
 */
char	*ms_expander(char *str, t_main *main)
{
	int		i;
	int		length;
	char	*result;
	char	*temp;

	i = 0;
	result = malloc(1);
	result[0] = '\0';
	while (str[i] != '\0')
	{
		length = expander_advanced(str + i);
		temp = expander_interpret(str + i, length, main);
		result = ms_strjoin_free(result, temp);
		i += length;
	}
	return (result);
}

/**
 * @brief Calculate the length that the string need to move forward to intepret
 * the next part of the string. For example, when the first character is not $,
 * move until encounter $ or quote. There are 3 condition.
 * 1) encounter a quote, move after the quote
 * 2) encounter $ sign, refer to get_expand_length
 * 3) other condition, move until end or encounter $ or quote
 */
int	expander_advanced(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
		return (ms_check_enclosed_length(str));
	if (str[i] == '$')
		return (get_expand_length(str));
	else
	{	
		while (str[i] != '$' && str[i] != '\0' && str[i] != '\''
			&& str[i] != '\"')
			i ++;
	}
	return (i);
}

/**
 * @brief Intepret the string, either duplicate or expand the variable.
 * There are 3 conditions
 * 1) First character is not $ sign or double quote, duplicate till length
 * 2) First character is $ sign, check for second character.
 * 3) First character is double quote and string contain $ sign, 
 * 		move until found $ sign, interpret like condition 2.
 *  	The return string is inclusive of quote sign.
 */
static char	*expander_interpret(char *str, int length, t_main *main)
{
	char	*rtn;

	if (*str != '$' && *str != '\"')
		rtn = ms_strdup_length(str, length);
	else if (*str == '\"')
		rtn = ms_intepret_quote(str, main);
	else
		rtn = ms_intepret_string(str, length, main);
	return (rtn);
}

/**
 * @brief Intepret a string that start with $ sign. Have 4 conditions
 * 1) Second character is also $, return empty string.
 * 2) Second character is ?, return global error
 * 3) Second character is not a valid env character, return "$"
 * 4) Second character is valid env character, expand the variable
 */
char	*ms_intepret_string(char *str, int length, t_main *main)
{
	int		i;
	char	*rtn;

	i = 1;
	if (str[i] == '$')
		rtn = ms_create_empty_string();
	else if (str[i] == '?')
		rtn = ft_itoa(g_error);
	else if (!ms_is_env_character(str[i]))
		rtn = ft_strdup("$");
	else
		rtn = ms_expand_string(str, length, main);
	return (rtn);
}
