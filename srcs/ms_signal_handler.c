/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:56:21 by zah               #+#    #+#             */
/*   Updated: 2023/01/13 16:39:08 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Change the default action of respective signal pass through.
 * Only handle SIGINT (ctrl-c) & SIGQUIT (ctrl-\\)
 * @param signum 
 * 
 */
void	handle_signal(int signum)
{	
	if (signum == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_error = 1;
	}
}

/**
 * @brief Initialize the signal handler to enable the program to detect
 * and handle signal. Also change the termios to turn off echo.
 * ECHOCTL is used instead of echo as it handle special character like ^C
 */
void	ms_init_sig_handler(void)
{
	struct sigaction	sa;
	struct sigaction	ignore;
	struct termios		current_termios;

	if (tcgetattr(STDIN_FILENO, &current_termios) != 0)
	{
		perror ("tcgetatter failed\n");
		exit (errno);
	}
	current_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &current_termios) != 0)
	{
		perror("tcsetattr failed\n");
		exit (errno);
	}
	sa.sa_handler = handle_signal;
	ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGQUIT, &ignore, NULL);
}
