/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:58:58 by zah               #+#    #+#             */
/*   Updated: 2022/12/20 15:50:18 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_logic(t_dlist *token_list);
static void		set_file_name(t_dlist *current, t_dlist *next);
static t_dlist	*parser_advance(t_dlist *current, int length);
static void		create_command(t_dlist *command_list, t_dlist *token,
					int length);

/**
 * @brief Turn the token list into a list to t_command.
 * First, check the token has correct logic and arrangement.
 * Then creating t_command list by, converting continuous word or
 * quote token to double array, assigning infile and outfile,
 * creating a new t_command node when encounter pipe token
 */
void	ms_parse_input(t_dlist *token_list, t_main *main)
{
	t_dlist		*current;
	t_dlist		*command_list;
	int			length;

	//Remove this line
	(void) main;
	if (!check_logic(token_list))
		printf("parser error\n");
	else
	{
		current = token_list;
		command_list = NULL;
		ms_dlist_addback(&command_list, ms_dlist_new(ms_init_command()));
		while (current != NULL)
		{
			length = ms_get_command_length(current);
			create_command(command_list, current, length);
			current = parser_advance(current, length);
		}
		print_command_list(&command_list);
		//Execute at here
		//execute(t_dlist *command_list, main)
		//Call this in executor, use to free command list
		ms_dlist_clear(&command_list, &ms_free_command);
	}
	ms_dlist_clear(&token_list, &ms_free_token);
}

/**
 * @brief Check the logic of the token list.
 * 1) Pipe character cannot be the first token
 * 2)After a infile or outfile token, should be a word or quote token.
 * If true, delete the word or quote token and add them as value of file token
 * @return 1 if ok, 0 when error 
 */
static int	check_logic(t_dlist *token_list)
{
	t_dlist	*current;
	t_token	*token;
	t_token	*next;

	current = token_list;
	if (((t_token *)current->content)->type == TOKEN_PIPE)
		return (0);
	while (current != NULL)
	{
		token = (t_token *)current->content;
		if (token->type == TOKEN_AIN || token->type == TOKEN_AOUT
			|| token->type == TOKEN_IN || token->type == TOKEN_OUT)
		{
			if (current->next == NULL)
				return (0);
			next = (t_token *)current->next->content;
			if (next->type != TOKEN_QUOTE && next->type != TOKEN_WORD)
				return (0);
			set_file_name(current, current->next);
		}
		current = current->next;
	}
	return (1);
}

/**
 * @brief Set the file name of the infile or outfile token
 * as the value of next token. After that delete the next token
 */
static void	set_file_name(t_dlist *current, t_dlist *next)
{
	t_token	*current_token;
	t_token	*next_token;

	current_token = (t_token *)current->content;
	next_token = (t_token *)next->content;
	current_token->value = ft_strdup(next_token->value);
	ms_dlst_del_target(&current, next, ms_free_token);
}

/**
 * @brief Move the linked list pointer by length
 */
static t_dlist	*parser_advance(t_dlist *head, int length)
{
	t_dlist	*current;
	int		i;

	current = head;
	i = 0;
	while (i < length)
	{
		current = current->next;
		i ++;
	}
	return (current);
}

/**
 * @brief Intepret the token list and create command based on it.
 * First check the token type of the first node. If it is pipe,
 * initalize new command struct and add it to the list. Otherwise, 
 * just modify the command 
 */
static void	create_command(t_dlist *command_list, t_dlist *token, int length)
{
	t_command	*new;
	t_command	*current;
	t_token		*head;
	t_dlist		*last;

	head = (t_token *)token->content;
	if (head->type == TOKEN_PIPE)
	{
		new = ms_init_command();
		ms_dlist_addback(&command_list, ms_dlist_new(new));
	}
	else
	{
		last = ms_dlst_last(command_list);
		current = (t_command *)last->content;
		if (head->type == TOKEN_WORD || head->type == TOKEN_QUOTE)
			current->full_command = ms_get_command(current, token, length);
		else if (head->type == TOKEN_AIN || head->type == TOKEN_IN)
			current->infile = ms_get_file_info(current->infile, head);
		else
			current->outfile = ms_get_file_info(current->outfile, head);
	}
}
