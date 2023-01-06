/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/06 15:10:16 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_process(t_main *main, t_command *cmd)
{
	main->pid[main->counter] = fork();
	if (main->pid[main->counter] == -1)
		exit(0);
	if (main->pid[main->counter] == 0)
	{
		ft_get_values(main, cmd, STDIN_FILENO, STDOUT_FILENO);
		dup2(cmd->in_fd, STDIN_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);
		// if (unlink("temp") < 0)
		// 	write(cmd->out_fd, "Unlink failure\n", 15);
		// if (check_built_in(main, cmd))
		// 	exit(0);
		ft_execve(main, cmd);
	}
}

void	first_process(t_main *main, t_command *cmd)
{
	main->pid[0] = fork();
	if (main->pid[0] == -1)
		exit(0);
	if (main->pid[0] == 0)
	{
		ft_get_values(main, cmd, STDIN_FILENO, main->pipe[main->counter][1]);
		dup2(cmd->in_fd, STDIN_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);
		// if (unlink("temp") < 0)
		// 	write(cmd->out_fd, "Unlink failure\n", 15);
		close(main->pipe[main->counter][0]);
		close(main->pipe[main->counter][1]);
		// if (check_built_in(main, cmd))
		// 	exit(0);
		ft_execve(main, cmd);
	}
}

void	middle_process(t_main *main, t_command *cmd)
{
	close(main->pipe[main->counter - 1][1]);
	if (pipe(main->pipe[main->counter]) == -1)
		exit(0);
	main->pid[main->counter] = fork();
	if (main->pid[main->counter] == -1)
		exit(0);
	if (main->pid[main->counter] == 0)
	{
		ft_get_values(main, cmd, main->pipe[main->counter - 1][0], main->pipe[main->counter][1]);
		dup2(cmd->in_fd, STDIN_FILENO);
		close(main->pipe[main->counter - 1][0]);
		dup2(cmd->out_fd, STDOUT_FILENO);
		// if (unlink("temp") < 0)
		// 	write(cmd->out_fd, "Unlink failure\n", 15);
		close(main->pipe[main->counter][0]);
		close(main->pipe[main->counter][1]);
		// if (check_built_in(main, cmd))
		// 	exit(0);
		ft_execve(main, cmd);
	}
}

void	last_process(t_main *main, t_command *cmd)
{
	main->pid[main->counter] = fork();
	if (main->pid[main->counter] == -1)
		exit(0);
	if (main->pid[main->counter] == 0)
	{
		ft_get_values(main, cmd, main->pipe[main->counter - 1][0], STDOUT_FILENO);
		dup2(cmd->in_fd, STDIN_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);
		// if (unlink("temp") < 0)
		// 	write(cmd->out_fd, "Unlink failure\n", 15);
		close(main->pipe[main->counter - 1][0]);
		close(main->pipe[main->counter - 1][1]);
		// if (check_built_in(main, cmd))
		// 	exit(0);
		ft_execve(main, cmd);
	}
	close(main->pipe[main->counter - 1][0]);
	close(main->pipe[main->counter - 1][1]);
}

void	ft_execute(t_main *main, t_command *cmd, int len)
{
	if (len == 1)
	{
		single_process(main, cmd);
		waitpid(main->pid[main->counter], NULL, 0);
		return ;
	}
	if (main->counter == 0)
		first_process(main, cmd);
	else if (main->counter == len - 1)
		last_process(main, cmd);
	else
		middle_process(main, cmd);
}
