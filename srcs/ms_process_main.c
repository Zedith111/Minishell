/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/28 13:05:11 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_main *main, t_dlist **list)
{
	t_dlist	*lst;

	lst = *list;
	while (lst)
	{
		free_temp((t_command *)lst->content);
		lst = lst->next;
	}
	while (--main->counter >= 0)
		get_error_value();
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

void	get_error_value(void)
{
	int	child_pid;
	int	status;

	child_pid = 1;
	while (child_pid > 0)
		child_pid = waitpid(-1, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_error = (WEXITSTATUS(status));
}

void	process(t_main *main, t_dlist **list)
{
	t_dlist	*lst;
	int		len;

	main->pid = malloc(sizeof(pid_t) * lst_len(*list));
	main->pipe = malloc(sizeof(int *) * (lst_len(*list) - 1));
	lst = *list;
	len = lst_len(lst);
	while (main->counter < (lst_len(*list) - 1)
		&& main->counter <= (lst_len(*list) - 1))
	{
		main->pipe[main->counter] = malloc(sizeof(int) * 2);
		main->counter++;
	}
	main->counter = 0;
	if (main->counter < (lst_len(*list) - 1) && pipe(main->pipe[0]) == -1)
		exit(0);
	get_here_doc(list, main);
	while (lst)
	{
		ft_execute(main, (t_command *)lst->content, len);
		lst = lst->next;
		main->counter++;
	}
	ft_free(main, list);
}
