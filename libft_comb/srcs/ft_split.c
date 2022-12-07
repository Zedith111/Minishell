/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:41:04 by zah               #+#    #+#             */
/*   Updated: 2022/10/16 17:59:15 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_is_sep(char c, char delimiter)
{
	if (c == delimiter)
		return (1);
	return (0);
}

static size_t	ft_count_split(const char *s, char c)
{
	size_t	i;
	size_t	split_count;

	i = 0;
	split_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ft_is_sep(s[i], c) == 1)
			i ++;
		if (s[i] != '\0')
			split_count ++;
		while (s[i] != 0 && ft_is_sep(s[i], c) == 0)
			i ++;
	}
	return (split_count);
}

size_t	ft_count_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && ft_is_sep(s[i], c) == 0)
		i ++;
	return (i);
}

char	*ft_write_split(const char *s, char c)
{
	size_t	split_length;
	size_t	i;
	char	*split;

	i = 0;
	split_length = ft_count_word(s, c);
	split = (char *)malloc (split_length + 1);
	if (split == NULL)
		return (NULL);
	while (i < split_length)
	{
		split[i] = s[i];
		i ++;
	}
	split[i] = '\0';
	return (split);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	tab_counter;

	if (s == NULL)
		return (NULL);
	tab_counter = 0;
	i = 0;
	tab = (char **)malloc(sizeof(char *) * ((ft_count_split(s, c)) + 1));
	if (tab == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ft_is_sep(s[i], c) == 1)
			i ++;
		if (s[i] != '\0')
		{
			tab[tab_counter] = ft_write_split(s + i, c);
			tab_counter ++;
		}
		while (s[i] != '\0' && ft_is_sep(s[i], c) == 0)
			i ++;
	}
	tab[tab_counter] = 0;
	return (tab);
}
