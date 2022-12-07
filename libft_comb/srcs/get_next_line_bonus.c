/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:06:08 by zah               #+#    #+#             */
/*   Updated: 2022/07/21 08:01:59 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"

int		check_next_line(char *str);
char	*add_to_stash(int fd, char *stash);
char	*read_from_stash(char *stash);
char	*refresh_stash(char *stash);

char	*get_next_line(int fd)
{
	static char	*stash[1023];
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = add_to_stash(fd, stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	line = read_from_stash(stash[fd]);
	stash[fd] = refresh_stash(stash[fd]);
	return (line);
}

int	check_next_line(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*add_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		read_length;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	read_length = 1;
	while (check_next_line(stash) == 0 && read_length != 0)
	{
		read_length = read(fd, buffer, BUFFER_SIZE);
		if (read_length == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_length] = '\0';
		stash = ft_gnl_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*read_from_stash(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (stash[i] == '\0')
		return (NULL);
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	line = (char *)malloc(i + 2);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*refresh_stash(char *stash)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	result = (char *)malloc(ft_strlen(stash) - i++ + 1);
	if (result == NULL)
		return (NULL);
	j = 0;
	while (stash[i] != '\0')
	{
		result[j] = stash[i];
		j++;
		i++;
	}
	result[j] = '\0';
	free(stash);
	return (result);
}
