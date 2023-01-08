/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:04:30 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/08 17:10:00 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_command *cmd, char *limiter)
{
	char	*buf;

	cmd->in_fd = open(cmd->temp_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_printf(">");
	buf = get_next_line(0);
	while (buf != NULL && compare(buf, limiter))
	{
		//Add format string function before writting into temp file
		//Buffer contain string, expand the string inside
		write(cmd->in_fd, buf, ft_strlen(buf));
		free(buf);
		ft_printf(">");
		buf = get_next_line(0);
	}
	free(buf);
	close(cmd->in_fd);
}

void	get_here_doc(t_dlist **list)
{
	t_dlist	*lst;
	int		temp_id;

	temp_id = 1;
	lst = *list;
	while (lst)
	{
		get_temp_name((t_command *)lst->content, temp_id);
		heredoc_execute((t_command *)lst->content);
		temp_id++;
		lst = lst->next;
	}
}
