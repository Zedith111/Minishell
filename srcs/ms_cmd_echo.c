/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:35:47 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/09 18:01:20 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_echo(t_main *main, t_command *cmd)
{
	int	i;

	i = 1;
	(void)main;
	if (cmd->full_command[i] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	if (ft_strncmp(cmd->full_command[i], "-n", 2) == 0
		&& ft_strlen(cmd->full_command[1]) == 2)
		i++;
	while (cmd->full_command[i] != NULL)
	{
		ft_printf("%s", cmd->full_command[i]);
		if (cmd->full_command[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (!(ft_strncmp(cmd->full_command[1], "-n", 2) == 0
			&& ft_strlen(cmd->full_command[1]) == 2))
		ft_printf("\n");
}
