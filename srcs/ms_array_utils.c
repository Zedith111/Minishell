/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zah <zah@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:10:19 by zah               #+#    #+#             */
/*   Updated: 2022/12/19 16:53:14 by zah              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_array_size(char **arr);

/**
 * @brief Append a new string into double array
 */
char	**ms_array_append(char **arr, char *new)
{
	char	**rtn;
	int		i;
	int		size;

	i = 0;
	size = get_array_size(arr);
	rtn = malloc (sizeof(char *) * (size + 2));
	while (i < size)
	{
		rtn[i] = arr[i];
		i ++;
	}
	rtn[i] = ft_strdup(new);
	rtn[i + 1] = NULL;
	free (arr);
	return (rtn);
}

void	ms_del_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free (arr[i]);
		i ++;
	}
	free (arr);
}

static int	get_array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
