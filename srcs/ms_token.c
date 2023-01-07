/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:14:34 by zah               #+#    #+#             */
/*   Updated: 2023/01/07 17:05:24 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Create token first

/**
 * @brief Return a token node or a list of token node when input a string.
 * First check for first character of the string, if is special character,
 * just create the respective type of token. If is other than that, create
 * a word token. 
 * First calculate the length to move forward. Then check for the 
 * first character in the string.
 * 1) If the first character is space, create a new node and add
 * 		behind the previous node
 * 2) If the first character is single or double quote, trim the 
 * 		first quote and join it back to previous result
 * 3) Other than this, just join the string with the previous result
 * When creating the node, check
 */
t_dlist	*ms_tokenized(char *str)
{
	int		i;
	int		length;
	char	*content;
	char	*temp;
	t_dlist	*rtn;

	i = 0;
	rtn = NULL;
	content = malloc(1);
	content[0] = '\0';
	while (str[i] != '\0')
	{
		//interpret
		//advance
		if (str[i] == ' ')
		{
			//convert current string to token first
			//add the token to the list
		}
		else if (str[i] == '\"' || str[i] == '\'')
		{

		}
		else
		{
		}
	}
	// ms_dlist_addback(&rtn,)
	return (rtn);
}

/**
 * @brief Return the length that the tokenizer need to advance.
 * Check for the first character in the string, If is quote, then
 * return the enclosed length. If is space, move until it meet the 
 * next space. Or else, breaks when it meet a space or quote
 * and return the length.
 */
static int	tokenizer_advance(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"' || str[i] == '\'')
		return (check_enclosed(str, str[i]));
	if (str[i] == ' ' || str[i] == '\t')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i ++;
	}
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\"' || str[i] == '\'')
			break ;
		else
			i ++;
	}
	return (i);
}
