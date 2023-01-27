/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/27 12:28:04 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit(t_main *main, t_command *cmd)
{
	(void) main;
	if (cmd->full_command[0] == NULL)
		return (0);
	if (ms_get_built_in(cmd->full_command[0]) == 7)
	{
		ms_cmd_exit(cmd);
		return (1);
	}
	return (0);
}

void	single_process(t_main *main, t_command *cmd)
{
	if (check_exit(main, cmd))
		return ;
	signal(SIGINT, SIG_IGN);
	main->pid[main->counter] = fork();
	if (main->pid[main->counter] == -1)
		exit(0);
	if (main->pid[main->counter] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		sort_in_out(main, cmd, STDIN_FILENO, STDOUT_FILENO);
		dup2(cmd->in_fd, STDIN_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);
		if (access(cmd->temp_name, F_OK) == 0)
			unlink(cmd->temp_name);
		if (check_built_in(main, cmd))
			exit(0);
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		sort_in_out(main, cmd, STDIN_FILENO, main->pipe[main->counter][1]);
		dup2(cmd->in_fd, STDIN_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);
		if (access(cmd->temp_name, F_OK) == 0)
			unlink(cmd->temp_name);
		close(main->pipe[main->counter][0]);
		close(main->pipe[main->counter][1]);
		if (check_built_in(main, cmd))
			exit(0);
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		sort_in_out(main, cmd, main->pipe[main->counter - 1][0],
			main->pipe[main->counter][1]);
		dup2(cmd->in_fd, STDIN_FILENO);
		close(main->pipe[main->counter - 1][0]);
		dup2(cmd->out_fd, STDOUT_FILENO);
		if (access(cmd->temp_name, F_OK) == 0)
			unlink(cmd->temp_name);
		close(main->pipe[main->counter][0]);
		close(main->pipe[main->counter][1]);
		if (check_built_in(main, cmd))
			exit(0);
		ft_execve(main, cmd);
	}
	close(main->pipe[main->counter - 1][0]);
}

void	last_process(t_main *main, t_command *cmd)
{
	char	buf[20];

	main->pid[main->counter] = fork();
	if (main->pid[main->counter] == -1)
		exit(0);
	if (main->pid[main->counter] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		sort_in_out(main, cmd, main->pipe[main->counter - 1][0], STDOUT_FILENO);
		dup2(cmd->in_fd, STDIN_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);
		if (access(cmd->temp_name, F_OK) == 0)
			unlink(cmd->temp_name);
		read(main->pipe[main->counter - 1][1], &buf, 10);
		close(main->pipe[main->counter - 1][0]);
		close(main->pipe[main->counter - 1][1]);
		if (check_built_in(main, cmd))
			exit(0);
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
		return ;
	}
	if (main->counter == 0)
		first_process(main, cmd);
	else if (main->counter == len - 1)
		last_process(main, cmd);
	else
		middle_process(main, cmd);
}
