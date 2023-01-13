/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:01:22 by zah               #+#    #+#             */
/*   Updated: 2023/01/10 15:46:31 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_env(t_main *main, t_command *cmd)
{
	t_dlist	*current;
	t_env	*env_node;

	(void)cmd;
	current = main->env_list;
	while (current != NULL)
	{
		env_node = (t_env *)current->content;
		if (env_node->value != NULL)
			printf("%s=%s\n", env_node->key, env_node->value);
		current = current->next;
	}
}
