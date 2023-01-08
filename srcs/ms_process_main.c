/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/06 16:37:34 by ojing-ha         ###   ########.fr       */
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

void	free_temp(t_command *cmd)
{
	free(cmd->temp_name);
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
	lst = *list;
	while (lst)
	{
		free_temp((t_command *)lst->content);
		lst = lst->next;
	}
	while (--main->counter >= 0)
		waitpid(-1, NULL, 0);
	main->counter = 0;
	while (main->counter < (lst_len(*list) - 1))
	{
		free(main->pipe[main->counter]);
		main->counter++;
	}
	main->counter = 0;
	free(main->pid);
	free(main->pipe);
}
