/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:21:49 by zah               #+#    #+#             */
/*   Updated: 2023/01/28 12:51:04 by ojing-ha         ###   ########.fr       */
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
	exit (0);
}
