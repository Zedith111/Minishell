/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:55:38 by zah               #+#    #+#             */
/*   Updated: 2022/12/07 15:23:35 by zah              ###   ########.fr       */
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
