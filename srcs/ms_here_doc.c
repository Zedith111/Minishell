/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:04:30 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/02 19:20:09 by ojing-ha         ###   ########.fr       */
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

void	here_doc(t_command *cmd, char *limiter)
{
	char	*buf;

	cmd->in_fd = open("temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// ft_printf(">");
	buf = readline(">");
	while (buf != NULL && compare(buf, limiter))
	{
		//Add format string function before writting into temp file
		write(cmd->in_fd, buf, ft_strlen(buf));
		free(buf);
		// ft_printf(">");
		buf = readline(">");
	}
	free(buf);
	close(cmd->in_fd);
}
