/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:27:55 by zah               #+#    #+#             */
/*   Updated: 2022/07/04 13:20:58 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;
	size_t			i;

	dest_c = (unsigned char *)dest;
	src_c = (unsigned char *)src;
	i = -1;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src_c < dest_c)
	{
		while (n-- > 0)
		{
			dest_c[n] = src_c[n];
		}
	}
	else
	{
		while (++i < n)
			dest_c[i] = src_c[i];
	}
	return (dest_c);
}
