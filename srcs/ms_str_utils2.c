/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_str_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 20:51:57 by zah               #+#    #+#             */
/*   Updated: 2023/01/10 17:35:55 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Join two string and free all memory. Src is the string
 * you want to join to
 */
char	*ms_strjoin_free(char *src, char *new)
{
	char	*rtn;

	rtn = ft_strjoin(src, new);
	free (src);
	free (new);
	return (rtn);
}
