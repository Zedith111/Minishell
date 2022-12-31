/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:37:05 by zah               #+#    #+#             */
/*   Updated: 2022/12/31 02:30:07 by ojing-ha         ###   ########.fr       */
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
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft_comb/includes/libft.h"
# include "../libft_comb/includes/ft_printf.h"
# include "../libft_comb/includes/get_next_line_bonus.h"

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


typedef struct s_file
{
	char	file_type;
	char	*file_name;
}	t_file;

/**
 * @brief The struct used to store commands after parsing.
 * Contain commands saved in **full_command, infile & outfile name, fopen type.
 */
typedef struct s_command
{
	char	**full_command;
	t_file	**infile;
	t_file	**outfile;

	int		in_fd;
	int		out_fd;
}	t_command;

/**
 * @brief 
 * Store a linked list of environment struct which will be updated whenever
 * a variable has been exported
 */
typedef struct s_main
{
	t_dlist		*env_list;
	char		**envp;

	pid_t		*pid;
	int			*pipe;
	int			last_pipe;
	int			counter;
}	t_main;

//Exit Function
void		ms_success_exit(t_main *main);
void		ms_error_exit(char *err_msg);

//String Utility Finction
int			ms_is_empty_string(char *str);
int			ms_char_match(char *str, char c);
int			ms_strcmp(char *s1, char *s2);

//Array Utility Function
char		**ms_array_append(char **arr, char *new);
void		ms_del_array(char **arr);
char		**ms_dup_array(char **arr);

//Double Linked List Function
t_dlist		*ms_dlist_new(void *content);
void		ms_dlist_addback(t_dlist **list, t_dlist *node);
void		ms_dlist_clear(t_dlist **lst, void (*del)(void *));
void		ms_dlist_del_first(t_dlist **lst, void (*del)(void *));
void		ms_dlst_del_last(t_dlist **lst, void (*del)(void *));
void		ms_dlst_del_target(t_dlist **lst, t_dlist *target,
				void (*del)(void *));
int			ms_dlist_size(t_dlist *head);
t_dlist		*ms_dlst_last(t_dlist *head);

//Signal Function
void		ms_init_sig_handler(void);

//Lexer and Expander
void		ms_process_input(char *input, t_main *main);
int			ms_is_sep(char c);
t_token		*ms_create_token(t_token_type type, char *value);
t_token		*ms_create_quote_token(t_lexer *lexer);
t_token		*ms_create_word_token(t_lexer *lexer);
t_token		*ms_create_operator_token(t_lexer *lexer);
void		ms_trim_list(t_dlist *head);
void		ms_expand_list(t_dlist *head, t_main *main);

//Parser
void		ms_parse_input(t_dlist *token_list, t_main *main);
t_file		*ms_init_tfile(void);
void		ms_set_tfile(t_file *target, char type, char *file_name);
t_file		**ms_append_tfile_array(t_file **files, char type, char *file_name);
t_command	*ms_init_command(void);
void		create_command(t_dlist *command_list, t_dlist *token, int length);
int			ms_get_command_length(t_dlist *token_list);
char		**ms_get_command(t_command *current, t_dlist *token_list,
				int length);
t_file		**ms_get_file_info(t_file **current, t_token *token);

//Built in command function
t_dlist		*ms_dup_env(char **envp);
void		ms_env_free(void *env);
void		ms_cmd_exit(void);

//Free function
void		ms_free_token(void *token);
void		ms_free_command(void *content);
void		ms_free_tfile_array(t_file **files);

//Testing use Function, will be deleted
void		print_token_node(t_dlist *node);
void		print_token_list(t_dlist **list);
void		print_env_list(t_dlist **lst);
void 		print_command_list(t_dlist **list);

//Execute functions
char	*ft_pathsort(t_main	*main, t_command *cmd);
void	ft_execve(t_main *main, t_command *cmd);

//Processes
void	print_error(char *str);
void	first_process(t_main *main, t_command *cmd);
void	middle_process(t_main *main, t_command *cmd);
void	last_process(t_main *main, t_command *cmd);

//Here_doc functions
void	here_doc(t_command *cmd, char *limiter);
void	process(t_main *main, t_dlist **lst);

#endif