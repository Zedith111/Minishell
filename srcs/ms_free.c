/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:32:53 by zah               #+#    #+#             */
/*   Updated: 2022/12/19 21:32:34 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Called by the parser once all the token has been converted to command
 */
void	ms_free_token(void *token)
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

	target = (t_command *)content;
	ms_del_array(target->full_command);
	ms_free_tfile_array(target->infile);
	ms_free_tfile_array(target->outfile);
	free (target);
}

void	ms_free_tfile_array(t_file **files)
{
	int	i;

	i = 0;
	while (files[i] != NULL)
	{
		free(files[i]->fine_name);
		free (files[i]);
		i ++;
	}
	free (files);
}
