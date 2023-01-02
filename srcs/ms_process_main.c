/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/02 19:32:54 by ojing-ha         ###   ########.fr       */
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
	if (len == 1)
	{
		single_process(main, cmd);
		// waitpid(main->pid[main->counter], NULL, 0);
		return ;
	}
	if (main->counter == 0)
	{
		printf("1\n");
		first_process(main, cmd);
		// waitpid(main->pid[main->counter], NULL, 0);
	}
	else if (main->counter == len - 1)
	{
		printf("3\n");
		last_process(main, cmd);
		// waitpid(main->pid[main->counter], NULL, 0);
	}
	else
	{
		printf("2\n");
		middle_process(main, cmd);
		// waitpid(main->pid[main->counter], NULL, 0);
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
	while (main->counter < (lst_len(*list) - 1)&& main->counter <= (lst_len(*list) - 1))
	{
		printf("PIpe %d\n", main->counter);
		main->pipe[main->counter] = malloc(sizeof(int) * 2);
		main->counter++;
	}
	main->counter = 0;
	if (main->counter < (lst_len(*list) - 1) && pipe(main->pipe[0]) == -1)
		exit(0);
	lst = *list;
	len = lst_len(lst);
	while (lst)
	{
		ft_execute(main, (t_command *)lst->content, len);
		lst = lst->next;
		main->counter++;
	}
	waitpid(main->pid[main->counter - 1], NULL, 0);
	main->counter = 0;
	// while (main->counter < lst_len(*list))
	// {
	// 	waitpid(main->pid[main->counter], NULL, 0);
	// 	main->counter++;
	// }
	free(main->pid);
	free(main->pipe);
}
