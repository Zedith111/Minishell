/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 20:44:43 by zah               #+#    #+#             */
/*   Updated: 2023/01/03 15:44:55 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_quote_front(int quote_count);
static char	*add_quote_back(char *str, int quote_count);
static int	get_normal_length(char *str);
static int	get_quote_count(char *str);

/**
 * @brief Intepret a string that start with quote.
 * 1) Count the number of single quote present in string
 * 2) Loop through the string and intepret like normal string
 * 		until it reach quote.
 * The return string is inclusive of all quote
 */
char	*ms_intepret_quote(char *str, t_main *main)
{
	int		i;
	int		quote_count;
	char	*rtn;

	i = get_quote_count(str);
	quote_count = i;
	rtn = add_quote_front(quote_count);
	while (str[i] != '\'' && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			rtn = ms_strjoin_free(rtn, ms_intepret_string(str + i,
						get_expand_length(str + i), main));
			i += get_expand_length(str + i);
		}
		else
		{
			rtn = ms_strjoin_free(rtn, ms_strdup_length(str + i,
						get_normal_length(str + i)));
			i += get_normal_length(str + i);
		}		
	}
	rtn = add_quote_back(rtn, quote_count);
	return (rtn);
}

/**
 * @brief Add the quote back to string based on number of quote.
 */
static char	*add_quote_front(int quote_count)
{
	char	*rtn;
	int		i;

	i = 1;
	rtn = malloc(quote_count + 1);
	rtn[0] = '\"';
	while (i < quote_count)
	{
		rtn[i] = '\'';
		i ++;
	}
	rtn[i] = '\0';
	return (rtn);
}

static char	*add_quote_back(char *str, int quote_count)
{
	char	*rtn;
	char	*temp;
	int		i;

	temp = malloc (quote_count + 1);
	i = 0;
	while (i < quote_count - 1)
	{
		temp[i] = '\'';
		i ++;
	}
	temp[i] = '\"';
	temp[i + 1] = '\0';
	rtn = ms_strjoin_free(str, temp);
	return (rtn);
}

/**
 * @brief Return the length when not encounter $ or quote.
 * Use to find the length when not needed to expand
 */
static int	get_normal_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i] != '\"' && str[i] != '\'')
		i ++;
	return (i);
}

static int	get_quote_count(char *str)
{
	int	i;

	i = 1;
	while (str[i] == '\'')
		i ++;
	return (i);
}
