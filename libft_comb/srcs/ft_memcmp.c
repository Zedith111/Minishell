/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:28:22 by zah               #+#    #+#             */
/*   Updated: 2022/07/05 08:06:27 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*str1_c;
	unsigned char	*str2_c;

	i = 0;
	str1_c = (unsigned char *)str1;
	str2_c = (unsigned char *)str2;
	while (i < n)
	{
		if (str1_c[i] == str2_c[i])
		{
			i ++;
		}
		else
			return (str1_c[i] - str2_c[i]);
	}
	return (0);
}
