/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:44:43 by zah               #+#    #+#             */
/*   Updated: 2022/11/28 15:15:23 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_input (void);

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	ms_init_sig_handler();
	while (1)
	{
		read_input();
	}
}

static void read_input(void)
{
	char	*line;

	line = readline("minishell>");
	if (line == NULL)
	{
		printf("exit");
		exit (0);
	}
	if (*line != '\0')
	{
		add_history(line);
		printf ("repeat\n");
		printf ("%s\n", line);
	}	
}