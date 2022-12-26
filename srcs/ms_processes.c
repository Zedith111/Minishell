/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2022/12/24 13:45:18 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_values(t_main *main, t_command *cmd)
{
	int	i;

	i = -1;
	(void)main;
	while (cmd->infile[++i] != NULL)
	{
		if (cmd->infile[i]->file_type == 'A')
			here_doc(cmd, cmd->infile[i]->file_name);
	}
	i = -1;
	while (cmd->infile[++i] != NULL)
	{
		if (cmd->infile[i + 1] == NULL)
		{
			if (cmd->infile[i]->file_type == 'A')
				cmd->in_fd = open("temp", O_RDONLY);
			else if (cmd->infile[i]->file_type == 'T')
				cmd->in_fd = open(cmd->infile[i]->file_name, O_RDONLY);
			else
				cmd->in_fd = STDIN_FILENO;
		}
	}
	i = -1;
	while (cmd->outfile[++i] != NULL)
	{
		if (cmd->outfile[i]->file_type == 'A')
			cmd->out_fd = open(cmd->outfile[i]->file_name,
				 O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			cmd->out_fd = open(cmd->outfile[i]->file_name,
				 O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (cmd->outfile[i + 1] != NULL)
			close(cmd->out_fd);
	}
}

void	first_process(t_main *main, t_command *cmd)
{
	main->pid[0] = fork();
	if (pipe(main->pipe) == -1)
		exit(0);
	if (main->pid[0] == -1)
		exit(0);
	if (main->pid[0] == 0)
	{
		ft_get_values(main, cmd);
		dup2(cmd->in_fd, STDIN_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);
		if (unlink("temp") < 0)
			printf("Unlink Failure");
		close(main->pipe[0]);
		close(main->pipe[1]);
		ft_execve(main, cmd);
	}
	waitpid(main->pid[0], NULL, 0);
}

void	ft_execute(t_main *main, t_command *cmd)
{
	first_process(main, cmd);
}

int		lst_len(t_dlist *list)
{
	int		count;
	t_dlist	*lst;

	lst = list;
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	process(t_main *main, t_dlist **list)
{
	t_dlist	*lst;

	main->pid = malloc(sizeof(__pid_t) * lst_len(*list));
	lst = *list;
	while (lst)
	{
		ft_execute(main, (t_command *)lst->content);
		lst = lst->next;
	}
}
