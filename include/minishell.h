/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:37:05 by zah               #+#    #+#             */
/*   Updated: 2022/12/04 17:25:01 by zah              ###   ########.fr       */
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

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

// Utility Function
void	ms_success_exit(void);
void	ms_error_exit(char *err_msg);
int		ms_is_empty_string(char *str);

//Double Linked List Function
t_dlist	*ft_dlist_new(void *content);
void	ft_dlist_addback(t_dlist **list, t_dlist *node);

//Signal Function
void	ms_init_sig_handler(void);

//Lexer and Expander
void	ms_process_input(char *input);
void	ms_tokenize(char *str, int stop, t_dlist **token_list);

//Testing use Function, will be destroyed
void	print_token_list(t_dlist **list);

#endif