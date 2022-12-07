/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:55:42 by zah               #+#    #+#             */
/*   Updated: 2022/07/05 17:52:28 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	total_len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	result = ft_calloc(total_len + 1, 1);
	if (result == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i ++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		result[i + ft_strlen(s1)] = s2[i];
		i ++;
	}
	result[i + ft_strlen(s1)] = '\0';
	return (result);
}
