/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:43:56 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/15 09:33:18 by zah              ###   ########.fr       */
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
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			while (paths[++i])
				free(paths[i]);
			return (cmd_path);
		}
		free(paths[i]);
		free(cmd_path);
		i++;
	}
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

void	ft_execve(t_main *main, t_command *cmd)
{
	char	*final_path;
	char	**current_envp;

	if (cmd->full_command[0] == NULL)
		exit (0) ;
	final_path = ft_pathsort(main, cmd);
	current_envp = ms_lst_to_env(main);
	if (access(final_path, F_OK) == 0)
	{
		execve(final_path, cmd->full_command, current_envp);
		free(final_path);
		ms_del_array(current_envp);
		return ;
	}
	else
	{
		print_error(cmd->full_command[0]);
		free(final_path);
		exit (0);
	}
}
