/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:37:05 by zah               #+#    #+#             */
/*   Updated: 2022/11/29 21:09:12 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_AIN,
	TOKEN_AOUT,
	TOKEN_PIPE
}	t_token_type;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

void	ms_success_exit(void);
void	ms_init_sig_handler(void);

#endif