/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:36:09 by zah               #+#    #+#             */
/*   Updated: 2022/12/15 14:00:10 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_token(void *content, t_main *main);
static char	*expand_variable(char *value, t_main *main);

/**
 * @brief Go through the token list and expand any variable present.
 * First check that the token type is word, then check that '$' is the 
 * first character of word and there are other character besides '$'.
 * After that, check if the word match to any key in env struct. 
 * If match, change value of the token to be the value of env struct.
 * If no key matches, return empty string
 * @param head Linked list that store the token struct
 */
void	ms_expand_list(t_dlist *head, t_main *main)
{
	t_dlist	*current;

	current = head;
	while (current != NULL)
	{
		expand_token(current->content, main);
		current = current->next;
	}
}

static void	expand_token(void *content, t_main *main)
{
	t_token	*token;
	char	*temp;

	token = (t_token *)content;
	if (token->type == TOKEN_WORD)
	{
		if (token->value[0] == '$' && token->value[1] == '?' && token->value[2] == '\0')
		{
			printf("exit status here\n");
		}
		else if (token->value[0] == '$' && token->value[1] != '\0')
		{
			temp = token->value;
			token->value = expand_variable(token->value, main);
			free(temp);
		}
	}
}

static char	*expand_variable(char *value, t_main *main)
{
	t_dlist	*current_env;
	t_env	*env;
	char	*rtn;

	current_env = main->env_list;
	while (current_env != NULL)
	{
		env = (t_env *)current_env->content;
		if (ms_strcmp(value + 1, env->key) == 0)
			return (ft_strdup(env->value));
		current_env = current_env->next;
	}
	rtn = malloc(1);
	rtn[0] = '\0';
	return (rtn);
}
