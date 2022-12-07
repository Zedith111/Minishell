/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:35:37 by zah               #+#    #+#             */
/*   Updated: 2022/08/05 09:54:49 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_count_size(unsigned int i)
{
	int	size;

	size = 1;
	while (i > 15)
	{
		i /= 16;
		size ++;
	}
	return (size);
}

static char	*ft_converthex(unsigned int i, char x)
{
	char	*s;
	int		size;

	size = ft_count_size(i);
	s = malloc(size + 1);
	if (s == NULL)
		return (NULL);
	s[size] = '\0';
	while (--size >= 0)
	{
		if (i % 16 <= 9)
		{
			s[size] = (i % 16) + '0';
			i /= 16;
		}
		else
		{
			if (x == 'x')
				s[size] = (i % 16) - 10 + 'a';
			else if (x == 'X')
				s[size] = (i % 16) - 10 + 'A';
			i /= 16;
		}
	}
	return (s);
}

int	ft_printhex(unsigned int i, char x)
{
	char	*s;
	int		len;

	len = 0;
	s = ft_converthex(i, x);
	len += ft_printstr(s);
	free(s);
	return (len);
}
