/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:32:54 by adesille          #+#    #+#             */
/*   Updated: 2024/08/23 08:00:12 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static t_string	*split_cwd(t_string cwd);
static void		update_cwd(t_cwd **cwd, const t_string new_dir);
static void		change_directory(t_cwd **current_dir, const t_string new_dir);

/**
 * 📋 Description: manages the current working directory based on the action.
 * 
 * @param cwd: the string representing the initial cwd.
 * @param new_dir: the directory to change to, if applicable.
 * @param action: the action to perform (INIT, UPDATE, GET, HOME).
 *
 * ⬅️ Return: t_string, the cwd as a string if action is GET or HOME.
 */
t_string	get_cwdd(const t_string cwd, t_string new_dir, const int action)
{
	static t_cwd	*current_cwd = NULL;
	static t_string	home = NULL;
	t_string		*dir_segments;

	if (action == INIT && cwd)
	{
		dir_segments = split_cwd(cwd);
		if (dir_segments)
			while (*dir_segments)
				add_node_cwd(&current_cwd, *dir_segments++);
		if (!home)
			home = get_envv(0, "HOME", FIND);
	}
	else if (action == UPDATE)
		change_directory(&current_cwd, new_dir);
	else if (action == GET)
		return (join_cwd(current_cwd));
	else if (action == HOME)
		return (home);
	return (NULL);
}

/**
 * 📋 Description: splits the cwd string into individual directory segments.
 * 
 * @param cwd: the string representing the current working directory.
 *
 * ⬅️ Return: t_string *, an array of directory segments.
 */
static t_string	*split_cwd(t_string cwd)
{
	t_string		*segments;
	t_string		seg_start;
	size_t			seg_index;
	const size_t	seg_count = count_dir(cwd);

	if (!cwd)
		return (NULL);
	segments = mem_manager((seg_count + 1) * sizeof(t_string), 0, 0, 'A');
	segments[seg_count] = NULL;
	seg_start = cwd;
	seg_index = 0;
	while (*cwd)
	{
		if (*cwd == '/' && *(cwd + 1) == '/')
			++cwd;
		else if (*cwd == '/' || !*(cwd + 1))
		{
			segments[seg_index++]
				= ft_substr(seg_start, 0, cwd - seg_start + 1);
			seg_start = ++cwd;
		}
		else
			++cwd;
	}
	return (segments);
}

/**
 * 📋 Description: changes the current directory based on the new directory.
 * 
 * @param current_dir: the pointer to the list representing the cwd.
 * @param new_dir: the target directory to switch to.
 *
 * ⬅️ Return: nothing.
 */
static void	change_directory(t_cwd **current_dir, const t_string new_dir)
{
	if (!current_dir || !new_dir || ft_strcmp(new_dir, "~") == EQUAL)
	{
		if (current_dir)
			*current_dir = NULL;
		get_cwdd(get_cwdd(0, 0, HOME), 0, INIT);
	}
	else if (*new_dir == '/')
	{
		*current_dir = NULL;
		if (ft_strcmp(new_dir, "/.") == EQUAL)
			new_dir[1] = '\0';
		get_cwdd(new_dir, 0, INIT);
	}
	else
		update_cwd(current_dir, new_dir);
}

/**
 * 📋 Description: updates the current directory by processing changes.
 * 
 * @param cwd: the pointer to the list representing the cwd.
 * @param new_dir: the new directory or segment to apply.
 *
 * ⬅️ Return: nothing.
 */
static void	update_cwd(t_cwd **current_dir, char *new_dir)
{
	t_cwd	*last_node;
	char	**cwd_dir;
	int		i;

	i = -1;
	last_node = *current_dir;
	while (last_node->next && last_node->next->next)
		last_node = last_node->next;
	cwd_dir = split_cwd(new_dir);
	while (cwd_dir[++i] && !ft_strncmp(cwd_dir[i], "..", 2))
	{
		last_node->next = NULL;
		last_node = *current_dir;
		while (last_node->next && last_node->next->next)
			last_node = last_node->next;
	}
	while (cwd_dir[i])
		add_node_cwd(current_dir, cwd_dir[i++]);
}
