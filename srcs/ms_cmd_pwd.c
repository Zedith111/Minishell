/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:14:47 by zah               #+#    #+#             */
/*   Updated: 2023/01/09 13:55:43 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmd_pwd(t_command *cmd)
{
	char	*buf;

	if (cmd->full_command[1] != NULL)
		printf("pwd: too many arguements\n");
	else
	{
		buf = getcwd(NULL, 0);
		printf("%s\n", buf);
		free (buf);
	}
}