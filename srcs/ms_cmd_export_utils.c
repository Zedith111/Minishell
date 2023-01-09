/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_export_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:08:47 by zah               #+#    #+#             */
/*   Updated: 2023/01/09 21:19:15 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_export_add(t_main *main, char **command)
{
	int	i;

	i = 1;
	while (command[i] != NULL)
	{
		//check whether has = sign, split when see the first = sign
		//export A===C, will cause A="==C"
		//check whether same variable present in current env
	}
	
}

