/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:44:16 by zah               #+#    #+#             */
/*   Updated: 2022/07/08 11:01:14 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_size(long n)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		n *= -1;
		size ++;
	}
	while (n > 9)
	{
		n /= 10;
		size ++;
	}
	return (size);
}

static void	ft_putnbr_arr(char *s, long n, int *i)
{
	if (n > 9)
	{
		ft_putnbr_arr(s, n / 10, i);
		ft_putnbr_arr(s, n % 10, i);
	}
	else
		s[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nbr;
	size_t	size;
	int		i;

	i = 0;
	nbr = n;
	size = ft_get_size(n);
	result = (char *)malloc(size + 1);
	if (result == NULL)
		return (NULL);
	if (nbr < 0)
	{
		result[i ++] = '-';
		nbr *= -1;
	}
	ft_putnbr_arr(result, nbr, &i);
	result[size] = '\0';
	return (result);
}
