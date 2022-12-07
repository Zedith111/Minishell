/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 12:23:58 by zah               #+#    #+#             */
/*   Updated: 2022/08/05 09:54:48 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printint(int i)
{
	char	*s;
	int		len;

	len = 0;
	s = ft_itoa(i);
	len += ft_printstr(s);
	free(s);
	return (len);
}
