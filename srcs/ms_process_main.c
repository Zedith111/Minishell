/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2022/12/31 00:59:41 by ojing-ha         ###   ########.fr       */
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

void	ft_execute(t_main *main, t_command *cmd, int len)
{
	(void)len;
	if (len == 1)
	{
		last_process(main, cmd);
		return ;
	}
	if (main->counter == 0)
	{
		first_process(main, cmd);
		// printf("first process\n");
	}
	else if (main->counter == len - 1)
	{
		last_process(main, cmd);
		// printf("last process\n");
	}
	else
	{
		middle_process(main, cmd);
		// printf("middle process\n");
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
	main->pipe = malloc(sizeof(int) * 2);
	if (pipe(main->pipe) == -1)
		exit(0);
	lst = *list;
	len = lst_len(lst);
	while (lst)
	{
		ft_execute(main, (t_command *)lst->content, len);
		waitpid(main->pid[main->counter], NULL, 0);
		lst = lst->next;
		main->counter++;
	}
	main->counter = 0;
	close(main->pipe[0]);
	close(main->pipe[1]);
	// while (main->counter > 0)
	// {
	// 	waitpid(main->pid[main->counter - 1], NULL, 0);
	// 	main->counter--;
	// }
	free(main->pid);
	free(main->pipe);
}
