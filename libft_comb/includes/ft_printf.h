/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:44:41 by zah               #+#    #+#             */
/*   Updated: 2022/08/03 09:17:38 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_check_format(char c, va_list ap);
int	ft_printchar(int c);
int	ft_printstr(char *s);
int	ft_printptr(void *ptr);
int	ft_printint(int i);
int	ft_printunsigned(unsigned int ui);
int	ft_printhex(unsigned int i, char x);

#endif