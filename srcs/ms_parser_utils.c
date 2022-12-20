/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:32:31 by zah               #+#    #+#             */
/*   Updated: 2022/12/20 15:40:34 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize the command struct. Both length of infile
 * and outfile is set as 2, being default and NULL
 */
t_command	*ms_init_command(void)
{
	t_command	*rtn;

	rtn = malloc (sizeof (t_command));
	rtn->full_command = malloc(sizeof(char *));
	rtn->full_command[0] = NULL;
	rtn->infile = malloc (sizeof(t_file *) * 2);
	rtn->infile[0] = ms_init_tfile();
	rtn->infile[1] = NULL;
	rtn->outfile = malloc (sizeof (t_file *) * 2);
	rtn->outfile[0] = ms_init_tfile();
	rtn->outfile[1] = NULL;
	return (rtn);
}

/**
 * @brief Calculate and return the amount of continuous word or quote token.
 * Return 1 for all other token
 */
int	ms_get_command_length(t_dlist *token_list)
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
	if (size == 0)
		size = 1;
	return (size);
}

/**
 * @brief Return an array of string that represent all the continuous word
 */
char	**ms_get_command(t_command *current, t_dlist *token_list, int length)
{
	char	**full_command;
	int		i;
	t_dlist	*current_token;
	t_token	*token;

	full_command = ms_dup_array(current->full_command);
	i = 0;
	current_token = token_list;
	while (i < length)
	{
		token = (t_token *)current_token->content;
		full_command = ms_array_append(full_command, token->value);
		i ++;
		current_token = current_token->next;
	}
	return (full_command);
}

/**
 * @brief Modify the infile and outfile of t_command struct.
 * First check that the current file name, if is NULL just modify the file name.
 * If is not NULL, append a new file to the double array
 */
t_file	**ms_get_file_info(t_file **current, t_token *token)
{
	char	file_type;
	t_file	**new;

	file_type = 'T';
	if (token->type == TOKEN_AIN || token->type == TOKEN_AOUT)
		file_type = 'A';
	if (current[0]->file_name == NULL)
	{
		ms_set_tfile(current[0], file_type, token->value);
		return (current);
	}
	else
	{
		new = ms_append_tfile_array(current, file_type, token->value);
		return (new);
	}
}
