/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:16:30 by zah               #+#    #+#             */
/*   Updated: 2022/07/04 16:17:57 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	i = ft_strlen(dest);
	j = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (n == 0 || n <= dest_len)
	{
		return (src_len + n);
	}
	while (src[j] != '\0' && j < n - dest_len - 1)
	{
		dest[i] = src[j];
		i ++;
		j ++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}
