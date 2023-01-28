/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:35:16 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/28 13:05:54 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, char *error_msg)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	exit (127);
}

int	check_built_in(t_main *main, t_command *cmd)
{
	if (cmd->full_command[0] == NULL)
		return (0);
	if (ms_get_built_in(cmd->full_command[0]) != 0)
	{
		if (ms_get_built_in(cmd->full_command[0]) == 1)
			ms_cmd_echo(cmd);
		if (ms_get_built_in(cmd->full_command[0]) == 2)
			ms_cmd_cd(main, cmd);
		if (ms_get_built_in(cmd->full_command[0]) == 3)
			ms_cmd_pwd(cmd);
		if (ms_get_built_in(cmd->full_command[0]) == 4)
			ms_cmd_export(main, cmd);
		if (ms_get_built_in(cmd->full_command[0]) == 5)
			ms_cmd_unset(main, cmd);
		if (ms_get_built_in(cmd->full_command[0]) == 6)
			ms_cmd_env(main, cmd);
		if (ms_get_built_in(cmd->full_command[0]) == 7)
			exit (0);
		return (1);
	}
	return (0);
}

int	lst_len(t_dlist *list)
{
	int		count;
	t_dlist	*lst;

	lst = list;
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	free_temp(t_command *cmd)
{
	free(cmd->temp_name);
}
