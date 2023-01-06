/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/06 15:10:23 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	write (2, str, ft_strlen(str));
	write(2, " :", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	ft_echo(t_main *main, t_command *cmd)
{
	int	i;

	i = 1;
	(void)main;
	if (ft_strncmp(cmd->full_command[i], "-n", 2) == 0)
		i++;
	while (cmd->full_command[i] != NULL)
	{
		write(cmd->out_fd, cmd->full_command[i], ft_strlen(cmd->full_command[i]));
		write(cmd->out_fd, " ", 1);
		i++;
	}
	if (!ft_strncmp(cmd->full_command[1], "-n", 2) == 0)
		write(cmd->out_fd, "\n", 1);
}

int		check_built_in(t_main *main, t_command *cmd)
{
	(void)main;
	if (cmd->full_command[0] == NULL)
		return (0);
	if (strncmp(cmd->full_command[0], "echo", 4) == 0)
	{
		ft_echo(main, cmd);
		return (1);
	}
	return (0);
}

void	ft_get_values(t_main *main, t_command *cmd, int in_fd, int out_fd)
{
	int	i;

	i = -1;
	(void)main;
	if (cmd->infile[0]->file_name == NULL)
		cmd->in_fd = in_fd;
	else
	{
		i = -1;
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
					print_error(cmd->infile[i]->file_name);
					exit (0);
				}
				if (cmd->infile[i + 1] != NULL)
					close(cmd->in_fd);
			}
		}
	}
	if (cmd->outfile[0]->file_name == NULL)
		cmd->out_fd = out_fd;
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
	int		len;

	main->pid = malloc(sizeof(pid_t) * lst_len(*list));
	main->pipe = malloc(sizeof(int *) * (lst_len(*list) - 1));
	lst = *list;
	len = lst_len(lst);
	while (main->counter < (lst_len(*list) - 1) && main->counter <= (lst_len(*list) - 1))
	{
		main->pipe[main->counter] = malloc(sizeof(int) * 2);
		main->counter++;
	}
	main->counter = 0;
	if (main->counter < (lst_len(*list) - 1) && pipe(main->pipe[0]) == -1)
		exit(0);
	get_here_doc(list);
	while (lst)
	{
		ft_execute(main, (t_command *)lst->content, len);
		lst = lst->next;
		main->counter++;
	}
	while (--main->counter >= 0)
		waitpid(-1, NULL, 0);
	main->counter = 0;
	free(main->pid);
	free(main->pipe);
}
