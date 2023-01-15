/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:46:07 by zah               #+#    #+#             */
/*   Updated: 2023/01/15 10:50:26 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check whether a character is a valid env character.
 * A valid env character is only consist of alphanumeric character 
 * and underscore only. 
 */
int	ms_is_env_character(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

/**
 * @brief Return the legth that need to advance when encounter $ sign.
 * There are 4 conditions.
 * 1) The next character is $, move until not $ or end of string.
 * 2) The next character is ?, return 2.
 * 3) The next character is not a valid env character, return 1.
 * 4) The next character is a valid env character, move until reach
 * a not valid env character
 */
int	get_expand_length(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '$')
	{
		while (str[i] != '\0')
		{
			if (str[i] != '$')
				break ;
			i ++;
		}	
	}
	else if (str[i] == '?')
		return (2);
	else if (!ms_is_env_character(str[i]))
		return (1);
	else
	{
		while (str[i] != '\0' && ms_is_env_character(str[i]))
			i ++;
	}
	return (i);
}

/**
 * @brief Expand the string by finding the same variable name
 * in current environment and return the value of the variable
 */
char	*ms_expand_string(char *str, int length, t_main *main)
{
	char	*cmp;
	char	*rtn;
	t_dlist	*current_env;
	t_env	*env;

	cmp = ms_strdup_length(str + 1, length - 1);
	current_env = main->env_list;
	rtn = NULL;
	while (current_env != NULL)
	{
		env = (t_env *)current_env->content;
		if (ms_strcmp(cmp, env->key) == 0)
			rtn = ft_strdup(env->value);
		current_env = current_env->next;
	}
	if (rtn == NULL)
	{
		rtn = malloc(1);
		rtn[0] = '\0';
	}
	free (cmp);
	return (rtn);
}

/**
 * @brief Add double quote in the front and back of string.
 * Also free the orginal string.
 */
char	*ms_append_quote(char *str)
{
	int		size;
	char	*rtn;
	int		i;

	size = ft_strlen(str);
	rtn = malloc (size + 3);
	i = 0;
	rtn[i] = '\"';
	while (i < size)
	{
		rtn[i + 1] = str[i];
		i ++;
	}
	rtn[i + 1] = '\"';
	rtn[i + 2] = '\0';
	free (str);
	return (rtn);
}
