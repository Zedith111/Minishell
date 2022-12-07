/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:22:38 by zah               #+#    #+#             */
/*   Updated: 2022/07/09 14:41:32 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		i;
	int		multiplier;
	long	result;

	i = 0;
	multiplier = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i ++;
	if (str[i] == '-')
		multiplier = -1;
	if (str[i] == '+' || str[i] == '-')
		i ++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (result * multiplier > 2147483647)
			return (-1);
		if (result * multiplier < -2147483648)
			return (0);
		i ++;
	}
	return (result * multiplier);
}
