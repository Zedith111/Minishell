/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tfile_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:55:47 by zah               #+#    #+#             */
/*   Updated: 2022/12/22 04:12:53 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_tfile_length(t_file **files);

/**
 * @brief Initialize the t_file struct, default file type is set to T
 * and default file name is set to NULL, default fd is set to 0
 */
t_file	*ms_init_tfile(void)
{
	t_file	*rtn;

	rtn = malloc (sizeof (t_file));
	rtn->file_type = 'T';
	rtn->file_name = NULL;
	return (rtn);
}

/**
 * @brief Append new t_file struct to the current t_file array
 */
t_file	**ms_append_tfile_array(t_file **files, char type, char *file_name)
{
	t_file	**rtn;
	t_file	*new;
	int		i;
	int		size;

	i = 0;
	size = get_tfile_length(files);
	rtn = malloc (sizeof (t_file *) * (size + 2));
	while (i < size)
	{
		rtn[i] = files[i];
		i ++;
	}
	new = ms_init_tfile();
	ms_set_tfile(new, type, file_name);
	rtn[i] = new;
	rtn[i + 1] = NULL;
	free (files);
	return (rtn);
}

/**
 * @brief Set the file type and file name of the target t_file struct
 */
void	ms_set_tfile(t_file *target, char type, char *file_name)
{
	if (target != NULL)
	{
		target->file_type = type;
		target->file_name = ft_strdup(file_name);
	}
}

static int	get_tfile_length(t_file **files)
{
	int	i;

	i = 0;
	while (files[i] != NULL)
		i ++;
	return (i);
}
