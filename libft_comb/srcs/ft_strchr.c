/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:37:17 by zah               #+#    #+#             */
/*   Updated: 2022/07/04 18:03:55 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)str;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
		{
			return (ptr + i);
		}
		i ++;
	}
	if (c == '\0')
		return (ptr + i);
	return (0);
}
