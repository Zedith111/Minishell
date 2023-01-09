/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:57:44 by zah               #+#    #+#             */
/*   Updated: 2023/01/09 21:10:19 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dlist	*env_list_dup(t_dlist *env_list);
static int		sort_envp(void	*a, void *b);
static void		export_print(t_main *main);
static void		export_add(t_main *main, char **command);

void	ms_cmd_export(t_main *main, t_command *cmd)
{
	if (cmd->full_command[1] == NULL)
		export_print(main);
	else
		export_add(main, cmd->full_command);

}

static t_dlist	*env_list_dup(t_dlist *env_list)
{
	t_dlist	*current;
	t_dlist	*dup;
	t_env	*current_node;
	t_env	*new_node;

	current = env_list;
	dup = NULL;
	while (current != NULL)
	{
		current_node  = (t_env *)current->content;
		new_node = malloc (sizeof (t_env));
		new_node->key = ft_strdup(current_node->key);
		new_node->value = ft_strdup(current_node->value);
		ms_dlist_addback(&dup, ms_dlist_new(new_node));
		current = current->next;
	}
	return (dup);
}

static int	sort_envp(void	*a, void *b)
{
	t_env	*env_a;
	t_env	*env_b;
	int		result;
	int		i;

	env_a = (t_env *)a;
	env_b = (t_env *)b;
	i = 0;
	while (env_a->key[i] != '\0' && env_b->key[i] != '\0')
	{
		if (env_a->key[i] == env_b->key[i])
			i ++;
		else
			break ;
	}
	result = env_a->key[i] < env_b->key[i];
	return (result);
}

static void		export_print(t_main *main)
{
	t_dlist	*dup;
	t_dlist	*current;
	t_env	*env;

	dup = env_list_dup(main->env_list);
	dup = ms_sort_list(dup, sort_envp);
	current = dup;
	while (current != NULL)
	{
		printf ("declare -x ");
		env = (t_env *)current->content;
		printf("%s=\"%s\"\n", env->key, env->value);
		current = current->next;
	}
	ms_dlist_clear(&dup, ms_env_free);
}