/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:32:53 by zah               #+#    #+#             */
/*   Updated: 2022/12/14 20:22:11 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Called by the parser once all the token has been converted to command
 */
void	ms_token_free(void *token)
{
	t_token	*target;

	target = (t_token *)token;
	free(target->value);
	free(target);
}

/**
 * @brief Called by the executor once the command has been excuted
 */
void	ms_free_command(void *content)
{
	t_command	*target;
	int			i;

	target = (t_command *)content;
	i = 0;
	while (target->full_command[i] != NULL)
	{
		free(target->full_command[i]);
		i++;
	}
	free(target->full_command);
}
