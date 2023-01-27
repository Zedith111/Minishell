/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:44:03 by zah               #+#    #+#             */
/*   Updated: 2023/01/27 14:47:01 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_val(t_dlist *node);

/**
 * @brief Convert the current list of environment value to double array,
 * used as variable for execve
 */
char	**ms_lst_to_env(t_main *main)
{
	int	size;
	int	i;
	char	**rtn;
	t_dlist	*current;

	size = ms_dlist_size(main->env_list);
	rtn = malloc (sizeof (char *) * (size + 1));
	i = 0;
	current = main->env_list;
	while (i < size)
	{
		rtn[i] = get_env_val(current);
		current = current->next;
		i ++;
	}
	rtn[i] = NULL;
	return (rtn);
}

static char	*get_env_val(t_dlist *node)
{
	t_env	*env;
	char	*rtn;
	char	*set;

	env = (t_env *)node->content;
	set = malloc(2);
	set[0] = '=';
	set[1] = '\0';
	rtn = ft_strjoin(env->key, set);
	rtn = ft_strjoin(rtn, env->value);
	free (set);
	return (rtn);
}