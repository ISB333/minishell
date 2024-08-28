/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:49:06 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/28 15:28:47 by adesille         ###   ########.fr       */
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
			if (!cwd->next && cwd->dir[index] == '/' && cwd->dir[0] != '/'
				&& index)
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
	size_t	len;
	t_cwd	*tmp;

	tmp = cwd;
	len = 0;
	while (tmp)
	{
		len += ft_strlen(tmp->dir);
		if (!tmp->next && tmp->dir[ft_strlen(tmp->dir) - 1] == '/'
			&& tmp->dir[0] != '/')
			len--;
		tmp = tmp->next;
	}
	return (len);
}
