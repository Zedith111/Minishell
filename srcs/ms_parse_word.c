/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:27:20 by zah               #+#    #+#             */
/*   Updated: 2022/12/15 20:56:24 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*init_command(void);
static char			*get_command(t_dlist *token);

//Malloc doubele array
//Parse word until pipe is reached
t_command	*ms_parse_word(t_dlist *token, int length)
{
	t_command	*rtn;
	t_dlist		*current;
	char		**cmd_arr;
	int			i;

	rtn = init_command();
	cmd_arr = malloc(sizeof(char *) * (length + 1));
	current = token;
	i = 0;
	while (i < length)
	{
		cmd_arr[i] = get_command(current);
		i ++;
		current = current->next;
	}
	cmd_arr[i] = NULL;
	printf("done parsing\n");

	return (rtn);
}

// return the duplicate of word
// char	*get_command

static t_command	*init_command(void)
{
	t_command	*rtn;

	rtn = malloc(sizeof(t_command));
	rtn->full_command = NULL;
	rtn->infile = "STDIN";
	rtn->outfile = "STDOUT";
	return (rtn);
}

static char	*get_command(t_dlist *token)
{
	t_token	*current;

	if (token == NULL)
		return (NULL);
	current = (t_token *)token->content;
	if (current->type == TOKEN_QUOTE || current->type == TOKEN_WORD)
		return (ft_strdup(current->value));
	return (NULL);
}