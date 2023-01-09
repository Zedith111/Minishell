/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:36:30 by zah               #+#    #+#             */
/*   Updated: 2023/01/09 15:35:16 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_dlist_size(t_dlist *head)
{
	t_dlist	*current;
	int		size;

	if (head == NULL)
		return (0);
	current = head;
	size = 0;
	while (current != NULL)
	{
		size ++;
		current = current->next;
	}
	return (size);
}

/**
 * @brief Delete a specific node in list
 */
void	ms_dlst_del_target(t_dlist **lst, t_dlist *target, void (*del)(void *))
{
	t_dlist	*current;

	if ((*lst) == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL && current != target)
		current = current->next;
	if (current->prev == NULL)
		ms_dlist_del_first(lst, del);
	else if (current->next == NULL)
		ms_dlst_del_last(lst, del);
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
		(*del)(current->content);
		free (current);
	}
}

t_dlist	*ms_dlst_last(t_dlist *head)
{
	t_dlist	*current;

	if (head == NULL)
		return (NULL);
	current = head;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

t_dlist	*ms_sort_list(t_dlist *lst, int (*cmp)(void *, void *))
{
	t_dlist	*tmp;
	void	*swap;

	tmp = lst;
	while(lst->next != NULL)
	{
		if (((*cmp)(lst->content, lst->next->content)) == 0)
		{
			swap = lst->content;
			lst->content = lst->next->content;
			lst->next->content = swap;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}