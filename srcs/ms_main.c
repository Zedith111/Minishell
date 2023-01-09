/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:44:43 by zah               #+#    #+#             */
/*   Updated: 2023/01/09 13:46:14 by zah              ###   ########.fr       */
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
	g_error = 0;
	main = init_main(envp);
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
	char	**built_in;

	rtn = malloc (sizeof(t_main));
	built_in = ft_split("echo cd pwd export unset env exit", ' ');
	rtn->env_list = ms_dup_env(envp);
	rtn->counter = 0;
	rtn->built_in = built_in;
	return (rtn);
}

/**
 * @brief Return a integer indicating which built in process will be used.
 * 0 if is not a built in.
 */
int	ms_get_built_in(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (1);
	if (strcmp(command, "cd") == 0)
		return (2);
	if (strcmp(command, "pwd") == 0)
		return (3);
	if (strcmp(command, "export") == 0)
		return (4);
	if (strcmp(command, "unset") == 0)
		return (5);
	if (strcmp(command, "env") == 0)
		return (6);
	if (strcmp(command, "exit") == 0)
		return (7);
	return (0);
}

// void	ms_free_main(t_main *main)
// {
// 	ms_dlist_clear(&main->env_list, &ms_env_free);
// }
