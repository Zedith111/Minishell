/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:32:31 by zah               #+#    #+#             */
/*   Updated: 2022/12/19 21:37:21 by zah              ###   ########.fr       */
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
	// rtn->full_command = malloc(sizeof (char *));
	// rtn->full_command[0] = NULL;
	rtn->infile = malloc (sizeof(t_file *) * 2);
	rtn->infile[0] = ms_init_tfile();
	rtn->infile[1] = NULL;
	rtn->outfile = malloc (sizeof (t_file *) * 2);
	rtn->infile[0] = ms_init_tfile();
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

char	**ms_get_command(t_dlist *token_list, int length)
{
	char	**full_command;
	int		i;
	t_dlist	*current;
	t_token	*token;

	full_command = malloc(sizeof(char *) * (length + 1));
	current = token_list;
	i = 0;
	while (i < length)
	{
		token = (t_token *)current->content;
		full_command[i] = ft_strdup(token->value);
		i ++;
		current = current->next;
	}
	full_command[i] = 0;
	return (full_command);
}


// void	ms_parse_file(t_dlist *token_list,void	*cmd)
// {
// 	t_command	*current;
// 	t_token		*token;

// 	token = (t_token *)token_list->content;
// 	current = (t_command *)cmd;
	
// }