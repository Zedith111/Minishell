/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:21:49 by zah               #+#    #+#             */
/*   Updated: 2022/12/28 14:24:10 by ojing-ha         ###   ########.fr       */
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
