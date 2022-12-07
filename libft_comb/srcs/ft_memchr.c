/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:08:13 by zah               #+#    #+#             */
/*   Updated: 2022/07/04 19:27:49 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;
	void	*ptr;

	i = -1;
	ptr = (void *)str;
	while (++i < n)
	{
		if (*(unsigned char *)(str + i) == (unsigned char)c)
			return (ptr + i);
	}
	return (0);
}
