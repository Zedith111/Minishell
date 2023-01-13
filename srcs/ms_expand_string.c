/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:37:04 by zah               #+#    #+#             */
/*   Updated: 2023/01/12 20:13:20 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Intepret a string that start with $ sign. 
 * Have 4 conditions based on the character behind the $ sign
 * 1) Second character is also $, return empty string.
 * 2) Second character is ?, return global error
 * 3) Second character is not a valid env character, return "$"
 * 4) Second character is valid env character, expand the variable
 * If the character before the $ sign is =, add double quote to the
 * return string
 */
char	*ms_intepret_string(t_expander *expander, char *str, int length, t_main *main)
{
	char	*rtn;
	int		i;

	rtn = NULL;
	i = 1;
	if (str[i] == '$')
		rtn = ms_create_empty_string();
	else if (str[i] == '?')
		rtn = ft_itoa(g_error);
	else if (!ms_is_env_character(str[i]))
		rtn = ft_strdup("$");
	else
	{
		rtn = ms_expand_string(str, length, main);
		if (expander->current != 0)
		{
			if (expander->input[expander->current - 1] == '=')
				rtn = ms_append_quote(rtn);
		}
	}
	return (rtn);
}
