/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:21:49 by zah               #+#    #+#             */
/*   Updated: 2022/12/03 14:05:39 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Exit the program when ctrl + d is pressed.
 * Output exit message and free.
 * @todo : Add free function
 */
void	ms_success_exit(void)
{
	printf("exit\n");
	exit (0);
}

/**
 * @brief Exit program when error occur.
 * Output error message and free
 * @param str Error message to display
 * @todo : Add free function. Free previoulsy generated lexer list
 */
void	ms_error_exit(char *err_msg)
{
	perror (err_msg);
	printf ("exiting\n");
	exit (1);
}
