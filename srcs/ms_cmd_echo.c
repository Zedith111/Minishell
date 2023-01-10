/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:35:47 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/10 16:51:24 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_echo_flag(char *str);
static int	get_flags_count(char **command);

void	ms_cmd_echo(t_command *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (cmd->full_command[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (check_echo_flag(cmd->full_command[i]) == 1)
		flag = 1;
	i = get_flags_count(cmd->full_command);
	if (cmd->full_command[i] == NULL)
		return ;
	while (cmd->full_command[i] != NULL)
	{
		printf("%s", cmd->full_command[i]);
		if (cmd->full_command[i + 1] != NULL)
			printf(" ");
		i ++;
	}
	if (flag == 0)
		printf("\n");
}

static int	check_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i ++;
	}
	return (1);
}

static int	get_flags_count(char **command)
{
	int	i;

	i = 1;
	while (command[i] != NULL)
	{
		if (check_echo_flag(command[i]) == 1)
			i ++;
		else
			break ;
	}
	return (i);
}