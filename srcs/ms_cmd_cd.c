/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:43:36 by zah               #+#    #+#             */
/*   Updated: 2023/01/10 11:06:55 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_main *main, char *search);

void	ms_cmd_cd(t_main *main, t_command *cmd)
{
	char	*path;

	if (cmd->full_command[1] == NULL
		|| ms_strcmp(cmd->full_command[1], "-") == 0)
	{
		if (cmd->full_command[1] == NULL)
			path = get_path(main, "HOME");
		else
			path = get_path(main, "OLDPWD");
		if (path == NULL)
			printf("cd : path not set\n");
		if (chdir(path) != 0)
			perror(path);
		free (path);
	}
	else if (chdir(cmd->full_command[1]) != 0)
		perror(cmd->full_command[1]);
}

/**
 * @brief Return the absolute path when cd has no arguement
 * or - as arguement
 */
static char	*get_path(t_main *main, char *search)
{
	t_dlist	*current;
	t_env	*env;

	current = main->env_list;
	while (current != NULL)
	{
		env = (t_env *)current->content;
		if (strcmp(search, env->key) == 0)
			return (ft_strdup(env->value));
		current = current->next;
	}
	return (NULL);
}