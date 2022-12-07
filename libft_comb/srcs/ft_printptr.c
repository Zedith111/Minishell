/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:56:54 by zah               #+#    #+#             */
/*   Updated: 2022/08/05 09:54:46 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_count_size(unsigned long long nbr)
{
	int	size;

	size = 1;
	while (nbr > 15)
	{
		nbr /= 16;
		size ++;
	}
	return (size);
}

static char	*ft_converthex(unsigned long long nbr)
{
	char	*s;
	int		size;

	size = ft_count_size(nbr);
	s = malloc(size + 1);
	if (s == NULL)
		return (NULL);
	s[size] = '\0';
	while (--size >= 0)
	{
		if (nbr % 16 <= 9)
		{
			s[size] = (nbr % 16) + '0';
			nbr /= 16;
		}
		else
		{
			s[size] = (nbr % 16) - 10 + 'a';
			nbr /= 16;
		}
	}
	return (s);
}

int	ft_printptr(void *ptr)
{
	unsigned long long	nbr;
	int					len;
	char				*s;

	len = 0;
	nbr = (unsigned long long)ptr;
	s = ft_converthex(nbr);
	len += ft_printstr("0x");
	len += ft_printstr(s);
	free (s);
	return (len);
}
