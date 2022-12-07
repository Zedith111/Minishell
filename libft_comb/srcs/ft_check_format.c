/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:37:25 by zah               #+#    #+#             */
/*   Updated: 2022/08/05 09:54:00 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_format(char c, va_list ap)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_printchar(va_arg(ap, int));
	else if (c == 's')
		len += ft_printstr(va_arg(ap, char *));
	else if (c == 'p')
		len += ft_printptr(va_arg(ap, void *));
	else if (c == 'd' || c == 'i')
		len += ft_printint(va_arg(ap, int));
	else if (c == 'u')
		len += ft_printunsigned(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		len += ft_printhex((va_arg(ap, unsigned int)), c);
	else if (c == '%')
		len += ft_printchar('%');
	return (len);
}
