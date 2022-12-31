/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:46:07 by zah               #+#    #+#             */
/*   Updated: 2022/12/30 20:34:02 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_expander_key(char *str)
{
	char	*rtn;
	int		i;
	int		length;

	i = 1;
	while (str[i] != '\0' && str[i] != '$' && str[i] != '\"')
		i ++;
	length = i;
	i = 1;
	rtn = malloc(length);
	while (i < length)
	{
		rtn[i - 1] = str[i];
		i++;
	}
	rtn[i- 1] = '\0';
	return (rtn);
}

int	ms_is_env_character(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}
