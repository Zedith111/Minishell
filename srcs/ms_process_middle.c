/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process_middle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/04 01:06:35 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_values_middle(t_main *main, t_command *cmd)
{
	int	i;

	i = -1;
	(void)main;
	while (cmd->infile[++i] != NULL)
	{
		if (cmd->infile[i]->file_type == 'A')
			here_doc(cmd, cmd->infile[i]->file_name);
	}
	if (cmd->infile[0]->file_name == NULL)
		cmd->in_fd = main->pipe[main->counter - 1][0];
	else
	{
		i = -1;
		while (cmd->infile[++i] != NULL)
		{
			if (cmd->infile[i + 1] == NULL)
			{
				if (cmd->infile[i]->file_type == 'A')
					cmd->in_fd = open("temp", O_RDONLY);
				else
					cmd->in_fd = open(cmd->infile[i]->file_name, O_RDONLY);
				if (cmd->in_fd == -1)
				{
					print_error(cmd->infile[i]->file_name);
					exit (0);
				}
				if (cmd->infile[i + 1] != NULL)
					close(cmd->in_fd);
			}
		}
	}
	if (cmd->outfile[0]->file_name == NULL)
		cmd->out_fd = main->pipe[main->counter][1];
	else
	{
		i = -1;
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
					print_error(cmd->outfile[i]->file_name);
					exit (0);
				}
			if (cmd->outfile[i + 1] != NULL)
				close(cmd->out_fd);
		}
	}
}

void	middle_process(t_main *main, t_command *cmd)
{
	printf("using pipe[%d]\n", main->counter);
	close(main->pipe[main->counter - 1][1]);
	if (pipe(main->pipe[main->counter]) == -1)
		exit(0);
	main->pid[main->counter] = fork();
	if (main->pid[main->counter] == -1)
		exit(0);
	if (main->pid[main->counter] == 0)
	{
		ft_get_values_middle(main, cmd);
		dup2(cmd->in_fd, STDIN_FILENO);
		close(main->pipe[main->counter - 1][0]);
		dup2(cmd->out_fd, STDOUT_FILENO);
		// if (unlink("temp") < 0)
		// 	write(cmd->out_fd, "Unlink failure\n", 15);
		close(main->pipe[main->counter][0]);
		close(main->pipe[main->counter][1]);
		if (check_built_in(main, cmd))
			exit(0);
		ft_execve(main, cmd);
	}
}