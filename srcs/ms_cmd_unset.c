/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:40:17 by zah               #+#    #+#             */
/*   Updated: 2023/01/10 17:34:10 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_variable(char *str);
static void	search_and_delete(t_dlist *env_list, char *str);

void	ms_cmd_unset(t_main *main, t_command *cmd)
{
	int		i;

	i = 1;
	while (cmd->full_command[i] != NULL)
	{
		if (!is_valid_variable(cmd->full_command[i]))
			printf("unset : not a valid identifier\n");
		else
			search_and_delete(main->env_list, cmd->full_command[i]);
		i ++;
	}
}

static int	is_valid_variable(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	else
	{
		while (str[i] != '\0')
		{
			if (!ms_is_env_character(str[i]))
				return (0);
			i ++;
		}
	}
	return (1);
}

static void	search_and_delete(t_dlist *env_list, char *str)
{
	t_dlist	*current;
	t_env	*env_node;

	current = env_list;
	while (current != NULL)
	{
		env_node = (t_env *)current->content;
		if (ms_strcmp(env_node->key, str) == 0)
		{
			ms_dlst_del_target(&env_list, current, ms_env_free);
			return ;
		}
		current = current->next;
	}
}
