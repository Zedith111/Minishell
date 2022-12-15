/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:37:05 by zah               #+#    #+#             */
/*   Updated: 2022/12/15 20:32:55 by zah              ###   ########.fr       */
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
# include "../libft_comb/includes/libft.h"
# include "../libft_comb/includes/ft_printf.h"

typedef enum s_token_type
{
	TOKEN_QUOTE,
	TOKEN_WORD,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_AIN,
	TOKEN_AOUT,
	TOKEN_PIPE,
	TOKEN_END,
	TOKEN_ERR
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

/**
 * @brief The lexer struct. 
 * Contain the original string as input
 * and pointer to the unprocess string as current
 */
typedef struct s_lexer
{
	char	*input;
	char	*current;
}	t_lexer;

/**
 * @brief The struct used to store encironment variable.
 * Contain two string, key the variable name, and the variable value.
 */
typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/**
 * @brief The struct used to store info to allow program to be execute.
 * Have a double array storing all command including arguement. A character 
 * named file type to check for whether should be Append (A) or Trunc (T)
 * Two string infile and outfile which is the name of infile and outfile
 */
typedef struct s_command
{
	char		**full_command;
	char		file_type;
	char		*infile;
	char		*outfile;
}	t_command;

/**
 * @brief 
 * Store a linked list of environment struct which will be updata whenever
 * a variable has been exported
 */
typedef struct s_main
{
	t_dlist		*env_list;
	char		**envp;
}	t_main;


//Exit Function
void	ms_success_exit(t_main *main);
void	ms_error_exit(char *err_msg);

//String Utility Finction
int		ms_is_empty_string(char *str);
int		ms_char_match(char *str, char c);
int		ms_strcmp(char *s1, char *s2);

//Double Linked List Function
t_dlist	*ms_dlist_new(void *content);
void	ms_dlist_addback(t_dlist **list, t_dlist *node);
void	ms_dlist_clear(t_dlist **lst, void (*del)(void *));
void	ms_dlist_del_front(t_dlist **lst, void (*del)(void *));
int		ms_dlist_size(t_dlist *head);

//Signal Function
void	ms_init_sig_handler(void);

//Lexer and Expander
void	ms_process_input(char *input, t_main *main);
int		ms_is_sep(char c);
t_token	*ms_create_token(t_token_type type, char *value);
t_token	*ms_create_quote_token(t_lexer *lexer);
t_token	*ms_create_word_token(t_lexer *lexer);
t_token	*ms_create_operator_token(t_lexer *lexer);
void	ms_trim_list(t_dlist *head);
void	ms_expand_list(t_dlist *head, t_main *main);

//Parser
void	ms_parse_input(t_dlist *token_list, t_main *main);

//Built in command function
t_dlist	*ms_dup_env(char **envp);
void	ms_env_free(void *env);
void	ms_cmd_exit(void);

//Free function
void	ms_token_free(void *token);
void	ms_free_main(t_main *main);

//Testing use Function, will be destroyed
void	print_token_node(t_dlist *node);
void	print_token_list(t_dlist **list);
void	print_env_list(t_dlist **lst);

#endif