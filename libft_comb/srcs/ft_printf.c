/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:11:54 by zah               #+#    #+#             */
/*   Updated: 2022/08/05 09:54:12 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, format);
	len = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			len += ft_check_format(*(format + 1), ap);
			format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			len ++;
		}
		format++;
	}
	va_end(ap);
	return (len);
}
