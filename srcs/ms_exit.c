/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:21:49 by zah               #+#    #+#             */
/*   Updated: 2023/01/08 15:35:35 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Exit the program when ctrl + d or exit detected.
 * Output exit message and free.
 */
void	ms_success_exit(t_main *main)
{
	(void) main;
	
	printf("exit\n");
	// ms_free_main(main);
	// system ("leaks minishell");
	exit (0);
}

/**
 * @brief Exit program and output error message when error occur.
 * Caution : this function is not responsible for freeing, please free beforehand
 * @param Error message to display
 */
void	ms_error_exit(char *err_msg)
{
	perror (err_msg);
	printf ("exiting\n");
	// system ("leaks minishell");
	exit (1);
}

// /**
//  * @brief Built in exit function
//  */
// void	ms_cmd_exit(void)
// {
// 	printf("exit");
// 	ms_success_exit();
// }
