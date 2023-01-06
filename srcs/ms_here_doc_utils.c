/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:04:30 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/06 14:51:21 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(char *buf, char *limit, int len)
{
	while (--len >= 0 && (*buf != '\0' || *buf != '\n'))
	{
		if (!(*buf == *limit))
			return (0);
		buf++;
		limit++;
	}
	if (*buf == '\0' || *buf == '\n')
		return (1);
	else
		return (0);
}

int	compare(char *buf, char *limiter)
{
	int	len;

	len = ft_strlen(limiter);
	if (buf == NULL)
		return (1);
	if (*buf == *limiter)
	{
		if (check(buf, limiter, len))
			return (0);
	}
	return (1);
}

void	get_temp_name(t_command *cmd, int temp_id)
{
	char	*id;

	id = ft_itoa(temp_id);
	cmd->temp_name = ft_strcat("temp", id);
	free(id);
}

void	heredoc_execute(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->infile[++i] != NULL)
	{
		if (cmd->infile[i]->file_type == 'A')
		{
			here_doc(cmd, cmd->infile[i]->file_name);
		}
	}
}

char	*ft_strcat(char *src, char *dst)
{
	char	*final;
	char	*ptr;

	final = malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(dst) + 1));
	final[ft_strlen(src) + ft_strlen(dst)] = '\0';
	ptr = final;
	while (*src != '\0')
	{
		*final = *src;
		src++;
		final++;
	}
	while (*dst != '\0')
	{
		*final = *dst;
		dst++;
		final++;
	}
	return (ptr);
}
