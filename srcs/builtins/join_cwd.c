/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:49:06 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/23 09:00:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static size_t	get_cwd_length(t_cwd *cwd);

/**
 * 📋 Description: assembles all parts of the cwd into a single string.
 * 
 * @param cwd: the list containing each part of the cwd.
 *
 * ⬅️ Return: t_string, the assembled cwd string.
 */
t_string	join_cwd(t_cwd *cwd)
{
	size_t		index;
	t_string	result;
	t_string	result_start;

	result = mem_manager(get_cwd_length(cwd) + 1, 0, 0, ALLOCATE);
	result_start = result;
	while (cwd)
	{
		index = 0;
		while (cwd->dir[index])
		{
			if (!cwd->next && cwd->dir[index] == '/' && index)
				break ;
			*result++ = cwd->dir[index++];
		}
		cwd = cwd->next;
	}
	*result = '\0';
	return (result_start);
}

/**
 * 📋 Description: calculates the total length of the cwd.
 * 
 * @param cwd: the list containing each part of the cwd.
 *
 * ⬅️ Return: size_t, the calculated total length.
 */
static size_t	get_cwd_length(t_cwd *cwd)
{
	size_t	length;
	size_t	dir_length;

	length = 0;
	while (cwd)
	{
		dir_length = ft_strlen(cwd->dir);
		if (dir_length)
		{
			length += dir_length;
			if (!cwd->next && cwd->dir[ft_strlen(cwd->dir) - 1] == '/'
				&& dir_length > 1)
				length--;
		}
		cwd = cwd->next;
	}
	return (length);
}
