/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sort_in_out_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:37:03 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/22 13:16:55 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_in(t_command *cmd, int i)
{
	while (cmd->infile[++i] != NULL)
	{
		if (cmd->infile[i + 1] == NULL)
		{
			if (cmd->infile[i]->file_type == 'A')
				cmd->in_fd = open(cmd->temp_name, O_RDONLY);
			else
				cmd->in_fd = open(cmd->infile[i]->file_name, O_RDONLY);
			if (cmd->in_fd == -1)
			{
				print_error(cmd->infile[i]->file_name, "Permission denied");
				exit (0);
			}
			if (cmd->infile[i + 1] != NULL)
				close(cmd->in_fd);
		}
	}
}

void	sort_out(t_command *cmd, int i)
{
	while (cmd->outfile[++i] != NULL)
	{
		if (cmd->outfile[i]->file_type == 'A')
			cmd->out_fd = open(cmd->outfile[i]->file_name,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			cmd->out_fd = open(cmd->outfile[i]->file_name,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (cmd->out_fd == -1)
		{
			print_error(cmd->outfile[i]->file_name, "Permission denied");
			exit (0);
		}
		if (cmd->outfile[i + 1] != NULL)
			close(cmd->out_fd);
	}
}

void	sort_in_out(t_main *main, t_command *cmd, int in_fd, int out_fd)
{
	(void)main;
	if (cmd->infile[0]->file_name == NULL)
		cmd->in_fd = in_fd;
	else
		sort_in(cmd, -1);
	if (cmd->outfile[0]->file_name == NULL)
		cmd->out_fd = out_fd;
	else
		sort_out(cmd, -1);
}
