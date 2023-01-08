/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:35:47 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/01/08 16:13:58 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_main *main, t_command *cmd)
{
	int	i;

	i = 1;
	(void)main;
	if (cmd->full_command[i] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	if (ft_strncmp(cmd->full_command[i], "-n", 2) == 0)
		i++;
	while (cmd->full_command[i] != NULL)
	{
		ft_printf("%s", cmd->full_command[i]);
		if (cmd->full_command[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (ft_strncmp(cmd->full_command[1], "-n", 2) != 0)
		ft_printf("\n");
}
