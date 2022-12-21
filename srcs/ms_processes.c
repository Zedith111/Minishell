/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_processes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2022/12/22 04:35:33 by ojing-ha         ###   ########.fr       */
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
			else
				cmd->in_fd = open(cmd->infile[i]->file_name, O_RDONLY);
		}
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
		// dup2(info->pipe[1], STDOUT_FILENO);
		// if (ft_strnstr(argv[1], "here_doc", 8))
		// {
		// 	if (unlink("temp") < 0)
		// 		print_error("Unlink Failure");
		// }
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
		printf("hi\n");
		ft_execute(main, (t_command *)lst->content);
		lst = lst->next;
	}
	// int	i;

	// i = 1;
	// here_doc()
	// first_process(info, argv, envp);
	// while (++i < info->process)
	// {
	// 	info->no++;
	// 	middle_process(info, i, argv, envp);
	// }
	// last_process(info, argc, argv, envp);
}
