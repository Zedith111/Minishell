/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:36:09 by zah               #+#    #+#             */
/*   Updated: 2023/01/27 12:08:33 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_expander	*init_expander(char *input);
static char			*expander_interpret(t_expander *expander, int length,
						t_main *main);

/**
 * @brief Take a string as input, expand all variable inisde.
 */
char	*ms_expander(char *str, t_main *main)
{
	t_expander	*expander;
	char		*result;
	char		*temp;
	int			length;

	expander = init_expander(str);
	result = ms_create_empty_string();
	while (expander->input[expander->current] != '\0')
	{
		length = expander_advanced(expander->input + expander->current);
		temp = expander_interpret(expander, length, main);
		result = ms_strjoin_free(result, temp);
		expander->current += length;
	}
	free (expander);
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
static char	*expander_interpret(t_expander *expander, int length, t_main *main)
{
	char	*rtn;
	char	*str;

	rtn = NULL;
	str = expander->input + expander->current;
	if (*str != '$' && *str != '\"')
		rtn = ms_strdup_length(str, length);
	else if (*str == '\"')
		rtn = ms_intepret_quote(expander, str, length, main);
	else
		rtn = ms_intepret_string(expander, str, length, main);
	return (rtn);
}

static t_expander	*init_expander(char *input)
{
	t_expander	*rtn;

	rtn = malloc (sizeof(t_expander));
	rtn->input = input;
	rtn->current = 0;
	return (rtn);
}
