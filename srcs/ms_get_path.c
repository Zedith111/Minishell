/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:43:56 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/28 12:57:16 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Extract the whole PATH= from envp	*/
char	**ft_path_extract(t_main *main)
{
	char	**paths;
	t_dlist	*lst;
	t_env	*content;

	lst = main->env_list;
	content = (t_env *)lst->content;
	paths = NULL;
	while (lst)
	{
		if (lst->next == NULL)
			return (NULL);
		if (ft_strncmp(content->key, "PATH", 5) == 0)
		{
			paths = ft_split(content->value, ':');
			return (paths);
		}
		lst = lst->next;
		content = (t_env *)lst->content;
	}
	return (paths);
}

/*	To Check which Path is the correct path for the OS	*/
/*	Returning The required path as "cmd_path"			*/
char	*ft_path_check(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (paths == NULL)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		free(paths[i]);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			while (paths[++i])
				free(paths[i]);
			free(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(paths);
	return (NULL);
}

/*	To Add a '/' character at the end of each extracted path	*/
char	**ft_pathcat(char **paths)
{
	char	**temp;
	int		x;
	int		count;

	x = 0;
	count = 0;
	if (paths == NULL)
		return (NULL);
	while (paths[count])
		count++;
	temp = malloc(sizeof(char *) * (count + 1));
	temp[count] = NULL;
	while (paths[x])
	{
		temp[x] = ft_strjoin(paths[x], "/");
		free(paths[x]);
		x++;
	}
	free(paths);
	return (temp);
}

// /*	To find the correct path and return it	*/
char	*ft_pathsort(t_main	*main, t_command *cmd)
{
	char	**paths;
	char	**temp;
	char	*cmd_path;

	paths = ft_path_extract(main);
	temp = ft_pathcat(paths);
	cmd_path = ft_path_check(temp, cmd->full_command[0]);
	return (cmd_path);
}

char	*check_path(t_dlist *list)
{
	t_dlist	*lst;
	t_env	*content;

	lst = list;
	content = (t_env *)lst->content;
	while (lst)
	{
		if (ft_strncmp(content->key, "PATH", 4) == 0)
			return ("PATH");
		lst = lst->next;
		if (lst != NULL)
			content = (t_env *)lst->content;
	}
	return (NULL);
}
