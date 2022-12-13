/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:44:15 by zah               #+#    #+#             */
/*   Updated: 2022/12/13 19:04:45 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env(char *str);

/**
 * @brief Duplicate current environment and add it to a linked list.
 * The data is store in the env struct, which contain two variable, key and value
 * @param envp Current environment array
 */
t_dlist	*ms_dup_env(char **envp)
{
	int		i;
	t_dlist	*head;

	i = 0;
	head = NULL;
	while (envp[i] != NULL)
	{
		ms_dlist_addback(&head, ms_dlist_new(create_env(envp[i])));
		i++;
	}
	return (head);
}

static t_env	*create_env(char *str)
{
	t_env	*rtn;
	char	*key;
	char	*value;

	rtn = malloc (sizeof(t_env));
	key = ft_substr(str, 0, ms_char_match(str, '='));
	value = ft_substr(str, ms_char_match(str, '=') + 1, ft_strlen(str));
	rtn->key = key;
	rtn->value = value;
	return (rtn);
}

/**
 * @brief Free the env struct
 */
void	ms_env_free(void *env)
{
	t_env	*target;

	target = (t_env *)env;
	free (target->key);
	free (target->value);
	free (target);
}
