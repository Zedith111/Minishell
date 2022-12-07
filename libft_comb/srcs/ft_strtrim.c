/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:53:21 by zah               #+#    #+#             */
/*   Updated: 2022/07/07 12:39:29 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_char_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	k;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] != '\0' && ft_char_in_set(s1[i], set))
		i++;
	while (j > i && ft_char_in_set(s1[j - 1], set))
		j--;
	result = (char *)malloc(j - i + 1);
	if (result == NULL)
		return (NULL);
	k = 0;
	while (i < j)
		result[k++] = s1[i++];
	result[k] = '\0';
	return (result);
}
