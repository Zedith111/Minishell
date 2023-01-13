/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_export_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:08:47 by zah               #+#    #+#             */
/*   Updated: 2023/01/10 17:33:51 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		has_value(char *str);
static int		search_and_replace(t_dlist *env_list, t_env *new);
static int		check_key_valid(char *str, int split);
static t_env	*create_new_env(char *str);

void	ms_export_add(t_main *main, char **command)
{
	int		i;
	t_env	*new;

	i = 1;
	while (command[i] != NULL)
	{
		new = create_new_env(command[i]);
		if (new != NULL)
		{
			if (search_and_replace(main->env_list, new) == 0)
				ms_dlist_addback(&main->env_list, ms_dlist_new(new));
		}
		i++;
	}
}

/**
 * @brief Check whether if the export argument has a value.
 * Return 0 if equal sign not found
 * If found equal sign, return the position of first equal sign
 */
static int	has_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static t_env	*create_new_env(char *str)
{
	int		split;
	t_env	*rtn;
	char	**empty_key;

	split = has_value(str);
	if (!check_key_valid(str, split))
	{
		printf("export : not a valid identifier\n");
		return (NULL);
	}
	rtn = malloc (sizeof (t_env));
	if (split != 0)
	{
		rtn->key = ms_strdup_length(str, split);
		rtn->value = ft_strdup(str + split + 1);
	}
	else
	{
		empty_key = ft_split(str, '=');
		rtn->key = ft_strdup(empty_key[0]);
		rtn->value = NULL;
		ms_del_array(empty_key);
	}
	return (rtn);
}

/**
 * @brief Check that the env list contain the same key name
 * as the newly created env. If contain duplicate, also check that
 * if the new env has value, and replace the original value 
 * if the new value if not NULL. 
 * Return 0 if no duplicate, 1 if have duplicate
 */
static int	search_and_replace(t_dlist *env_list, t_env *new)
{
	t_dlist	*current;
	t_env	*cmp;
	char	*temp;

	current = env_list;
	while (current != NULL)
	{
		cmp = (t_env *)current->content;
		if (ms_strcmp(cmp->key, new->key) == 0)
		{
			if (new->value != NULL)
			{
				temp = cmp->value;
				cmp->value = ft_strdup(new->value);
				free (temp);
			}
			ms_env_free(new);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	check_key_valid(char *str, int split)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	if (split != 0)
	{
		while (i < split)
		{
			if (!ms_is_env_character(str[i]))
				return (0);
			i ++;
		}
	}
	else
	{
		while (str[i] != '\0' && str[i] != '=')
		{
			if (!ms_is_env_character(str[i]))
				return (0);
			i ++;
		}
	}
	return (1);
}
