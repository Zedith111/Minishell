/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:33:42 by zah               #+#    #+#             */
/*   Updated: 2022/08/05 09:54:45 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printstr(char *s)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, 1);
		return (ft_strlen(s));
	}
	ft_putstr_fd("(null)", 1);
	return (6);
}
