/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:30:35 by zah               #+#    #+#             */
/*   Updated: 2022/12/30 20:33:53 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//$/ should came out $/-> add presert

static char	*expand_quote(char *str, int length, t_main *main);
static int	get_expand_length(char *str);
static int	expander_advanced(char *str);
static char	*expander_join(char *str, int length, char *prev, t_main *main);

/**
 * @brief Take a string as input, expand all variable inisde.
 */
char	*ms_expander(char *str, t_main *main)
{
	int		i;
	int		length;
	char	*result;

	i = 0;
	result = malloc(1);
	result[0] = '\0';
	while (str[i] != '\0')
	{
		length = expander_advanced(str + i);
		result = expander_join(str + i, length, result, main);
		i += length;
	}
	return (result);
}

static int	expander_advanced(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		return (get_expand_length(str));
	if (str[i] == '\'')
		return (ms_check_enclosed_length(str));
	else
	{	
		while (str[i] != '$' && str[i] != '\0')
			i ++;
	}
	return (i);
}

static char	*expander_join(char *str, int length, char *prev, t_main *main)
{
	int		i;
	char	*temp;
	char	*rtn;

	i = 0;
	if (str[i] != '$')
		temp = ms_strdup_length(str, length);
	else
	{
		i = 1;
		if (str[i] == '$')
			temp = ms_create_empty_string();
		else if (str[i] == '?')
			temp = ft_itoa(0);
		else if (str[i] == '\0' || str[i] == '\"')
			temp = ft_strdup("$");
		else if (ms_is_env_character(str[i]))
			temp = expand_quote(str, length, main);
		else
			temp = ms_strdup_length(str, length);
	}
	rtn = ft_strjoin(prev, temp);
	free (temp);
	free (prev);
	return (rtn);
}

/**
 * @brief Return the legth that need to advance when encounter $ sign.
 * If the next character is also $, move until not $ sign, or \0 or ".
 * If the next character is non $, move until is $, or not \0 or ".
 * If the next character is ?, return 2
 * if next character is end or quote, return 1
 */
static int	get_expand_length(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '?')
		return (2);
	if (str[i] == '\0' || str[i] == '\"')
		return (1);
	if (str[i] == '$')
	{
		while (str[i] == '$' && str[i] != '\0' && str[i] != '\"')
			i ++;
	}
	else
	{
		while (ms_is_env_character(str[i]) && str[i] != '\0' && str[i] != '\"')
			i ++;
	}
	return (i);
}

static char	*expand_quote(char *str, int length, t_main *main)
{
	char	*cmp;
	char	*rtn;
	t_dlist	*current_env;
	t_env	*env;

	cmp = ms_get_expander_key(str);
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
