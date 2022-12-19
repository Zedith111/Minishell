/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:36:30 by zah               #+#    #+#             */
/*   Updated: 2022/12/19 20:30:13 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Not sure required
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

void	ms_dlst_del_target(t_dlist **lst, t_dlist *target, void (*del)(void *))
{
	t_dlist	*current;

	if ((*lst) == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		if (current == target)
		{
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
		current = current->next;
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
