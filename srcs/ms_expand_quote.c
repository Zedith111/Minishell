/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 20:44:43 by zah               #+#    #+#             */
/*   Updated: 2023/01/28 12:51:25 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pre_process(char *str, int length);
static char	*process_quote(char *input, char *prev, t_expander *expander,
				t_main *main);
static int	get_normal_length(char	*input);

/**
 * @brief Intepret a string that start with double quote.
 * First trim off the double quote, then check for the remaining
 * string. duplicate until encouter $ or is end of string.
 * If encounter $ sign, expand it like normal string.
 * Finally, add the double quote back
 */
char	*ms_intepret_quote(t_expander *expander, char *str, int length,
				t_main *main)
{
	char	*input;
	char	*rtn;
	int		i;

	input = pre_process(str, length);
	i = 0;
	while (input[i] != '\0' && input[i] != '$')
		i++;
	rtn = ms_strdup_length(input, i);
	if (input[i] != '\0')
		rtn = process_quote(input + i, rtn, expander, main);
	rtn = ms_append_quote(rtn);
	free (input);
	return (rtn);
}

/**
 * @brief Receive a string start with double quote, duplicate it and
 * trim out the double quote
 */
static char	*pre_process(char *str, int length)
{
	char	*temp;
	char	*rtn;
	char	*quote;

	temp = ms_strdup_length(str, length);
	quote = malloc (2);
	quote[0] = '\"';
	quote[1] = '\0';
	rtn = ft_strtrim(temp, quote);
	free (temp);
	free (quote);
	return (rtn);
}

static char	*process_quote(char *input, char *prev, t_expander *expander,
			t_main *main)
{
	int		i;
	char	*temp;
	char	*rtn ;
	int		length;

	i = 0;
	rtn = prev;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			temp = ms_intepret_string(expander, input + i,
					get_expand_length(input + i), main);
			rtn = ms_strjoin_free(rtn, temp);
			i += get_expand_length(input + i);
		}
		else
		{
			length = get_normal_length(input + i);
			temp = ms_strdup_length(input + i, length);
			rtn = ms_strjoin_free(rtn, temp);
			i += length;
		}
	}
	return (rtn);
}

static int	get_normal_length(char	*input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			break ;
		i ++;
	}
	return (i);
}
