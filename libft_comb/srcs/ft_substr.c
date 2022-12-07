/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:54:31 by zah               #+#    #+#             */
/*   Updated: 2022/08/05 09:40:57 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start >= str_len)
		return (ft_calloc(1, 1));
	else if (len > str_len - start)
		result = (char *)malloc(str_len - start + 1);
	else
		result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		result[i] = s[i + start];
		i ++;
	}
	result[i] = '\0';
	return (result);
}
