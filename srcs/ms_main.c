/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:44:43 by zah               #+#    #+#             */
/*   Updated: 2022/12/12 14:38:14 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_input(void);

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	ms_init_sig_handler();
	while (1)
	{
		read_input();
	}
}

static void	read_input(void)
{
	char	*line;

	line = readline("minishell>");
	if (line == NULL)
		ms_success_exit();
	if (ms_is_empty_string(line))
	{
		free (line);
		return ;
	}
	if (*line != '\0' && line != NULL)
	{
		add_history(line);
		ms_process_input(line);
	}
	free (line);
}
