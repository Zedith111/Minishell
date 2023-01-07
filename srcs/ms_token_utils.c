/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:22:27 by zah               #+#    #+#             */
/*   Updated: 2023/01/07 16:51:14 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a node of token struct based on the input string
 */
t_dlist	*ms_create_token(char *str)
{
	t_token	*token;

	token = (t_token *)malloc (sizeof (t_token));

	return (ms_dlist_new(token));
}

/**
 * @brief Return the token type based on the c
 * 
 */
static t_token_type	