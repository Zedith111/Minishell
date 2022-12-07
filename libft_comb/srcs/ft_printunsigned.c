/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 12:33:31 by zah               #+#    #+#             */
/*   Updated: 2022/08/05 09:54:43 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_count_size(unsigned int ui)
{
	int	size;

	size = 1;
	while (ui > 9)
	{
		size ++;
		ui /= 10;
	}
	return (size);
}

static char	*ft_uitoa(unsigned int ui)
{
	char	*s;
	int		size;

	size = ft_count_size(ui);
	s = malloc(size + 1);
	if (s == NULL)
		return (NULL);
	s[size] = '\0';
	while (--size >= 0)
	{
		s[size] = (ui % 10) + '0';
		ui /= 10;
	}
	return (s);
}

int	ft_printunsigned(unsigned int ui)
{
	char	*s;
	int		len;

	len = 0;
	s = ft_uitoa(ui);
	len += ft_printstr(s);
	free (s);
	return (len);
}
