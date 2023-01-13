/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:07:21 by zah               #+#    #+#             */
/*   Updated: 2023/01/10 17:33:12 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_one_argument(char **command);

/**
 * @brief Built in exit command. 
 * Exit with no argument will exit with 0
 * Exit with 1 argument depend on the argument value
 * 	1) If argument contain number only will exit with the number. If the number
 * 		is more than 255, will return modulo of 256
 *  2) If argument contain other than number, will exit with 255
 * Exit with more than 2 argument will prompt too many arguement and not exit
 */
void	ms_cmd_exit(t_command *cmd)
{
	if (cmd->full_command[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (cmd->full_command[1] != NULL)
	{
		if (cmd->full_command[2] != NULL)
		{
			ft_putstr_fd("exit\nexit: too many argument\n", STDERR_FILENO);
			g_error = 1;
			return ;
		}
		else
			exit_one_argument(cmd->full_command);
	}
}

static void	exit_one_argument(char **command)
{
	int	i;
	int	val;

	i = 0;
	while (command[1][i] != '\0')
	{
		if (!ft_isdigit(command[1][i]))
		{
			ft_putstr_fd("exit\nexit: a numeric argument required\n",
				STDERR_FILENO);
			exit (255);
		}
		else
		{
			val = ft_atoi(command[1]);
			if (val > 255)
				val = val % 256;
			exit (val);
		}
	}
}
