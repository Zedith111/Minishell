/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:55:38 by zah               #+#    #+#             */
/*   Updated: 2022/12/13 16:05:20 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check that if a string is empty.Empty string contain space and 
 * tab only
 * @param str The string to check for 
 * @return 0 if not empty, 1 if empty
 */
int	ms_is_empty_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] != ' ' && str[i] != 9)
			return (0);
		i ++;
	}
	return (1);
}

/**
 * @brief Check if the character c is present in the string str
 * @return The position of the respective character, -1 if not present
 */
int	ms_char_match(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Compare 2 string to check that both are equal
 * @return The difference between two string, 0 if both are same
 */
int	ms_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i ++;
	}
	return (s1[i] - s2[i]);
}
