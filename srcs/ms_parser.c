/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:58:58 by zah               #+#    #+#             */
/*   Updated: 2022/12/15 14:24:05 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
if current token is word or quote, then check until not word or token
if current token is in/outfile, set the value
if current token is pipe, create new one
if no more token, break
*/

// char *get_word(t_dlist *token);
static int	get_command_length(t_dlist *token_list);

//Turn the token list to a list of command. Each command struct
//contain a double array of character represent the full command
//2 integer, representing infile and outfile. For example echo hello
//will become
//	"echo", "hello"
//	0
//	1
//This will break when encounter the pipe character. and create a new struct 
void	ms_parse_input(t_dlist *token_list, t_main *main)
{
	(void) main;
	// t_dlist	*cmd_list;
	t_dlist *current;
	int length;
	int i;
	
	current = token_list;
	while (current != NULL)
	{
		length = get_command_length(current);
		i = 1;
		print_token_node(current);
		//process
		//trim
		current = current->next;
		while ( i < length)
		{
			current = current->next;
			i ++;
		}
		
	}
	


	// char *command;

	// current = (t_token *)token->content;
	// if (current->type == TOKEN_QUOTE || current->type == TOKEN_WORD)
	// {
	// 	command = get_word(token);
	// 	while (command != NULL)
	// 	{
	// 		printf ("%s", command);
	// 		ms_dlist_del_front(&token, &ms_token_free);
	// 		command = get_word(token);
	// 		free (command);
	// 	}
	// 	printf("\nend\n");
		
	// }
	ms_dlist_clear(&token_list, &ms_token_free);
}





static int	get_command_length(t_dlist *token_list)
{
	t_dlist	*current;
	t_token	*token;
	int		size;

	current = token_list;
	size = 0;
	while (current != NULL)
	{
		token = (t_token *)current->content;
		if (token->type != TOKEN_WORD && token->type != TOKEN_QUOTE)
			break ;
		size ++;
		current = current->next;
	}
	return (size);
}

//Process token, return the address of dlist
