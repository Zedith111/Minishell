/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:10:02 by zah               #+#    #+#             */
/*   Updated: 2022/12/13 20:10:44 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ms_dlist_new(void *content)
{
	t_dlist	*node;

	node = malloc (sizeof (t_dlist));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ms_dlist_addback(t_dlist **list, t_dlist *node)
{
	t_dlist	*last;

	if (list == NULL || node == NULL)
		return ;
	if ((*list) == NULL)
		*list = node;
	else
	{
		last = *list;
		while (last->next != NULL)
			last = last->next;
		last->next = node;
		node->prev = last;
	}
}

void	ms_dlist_clear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*temp;

	if (lst == NULL || del == NULL)
		return ;
	while ((*lst) != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		(*del)(temp->content);
		free (temp);
	}
	*lst = NULL;
}
