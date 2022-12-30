/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:44:43 by zah               #+#    #+#             */
/*   Updated: 2022/12/28 15:36:28 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		read_input(t_main *main);
static t_main	*init_main(char **envp);
// static void		free_main(t_main *main);

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;

	(void) argc;
	(void) argv;
	main = init_main(envp);
	//Test print env
	// print_env_list(&main->env_list);
	ms_init_sig_handler();
	while (1)
	{
		read_input(main);
	}
}

static void	read_input(t_main *main)
{
	char	*line;

	line = readline("minishell>");
	if (line == NULL)
		ms_success_exit(main);
	if (ms_is_empty_string(line))
	{
		free (line);
		return ;
	}
	if (*line != '\0' && line != NULL)
	{
		add_history(line);
		ms_process_input(line, main);
	}
	free (line);
}

/**
 * @brief Initialize the main struct.
 * Duplicating the environment variable into a linked list
 */
static t_main	*init_main(char **envp)
{
	t_main	*rtn;

	rtn = malloc (sizeof(t_main));
	rtn->env_list = ms_dup_env(envp);
	rtn->counter = 0;
	return (rtn);
}

// void	ms_free_main(t_main *main)
// {
// 	ms_dlist_clear(&main->env_list, &ms_env_free);
// }
