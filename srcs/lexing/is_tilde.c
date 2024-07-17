/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:00:47 by isb3              #+#    #+#             */
/*   Updated: 2024/07/17 08:16:05 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_node_h(t_home **h, char *s)
{
	t_home	*new_node;
	t_home	*last_node;

	new_node = mem_manager(sizeof(t_home), 0, 0, 'A');
	new_node->next = NULL;
	new_node->dir = ft_substr(s, 0, ft_strlen(s)
			- ft_strlen(ft_strchr(s, ':')));
	s = ft_strchr(s, '/');
	new_node->path = ft_substr(s, 0, ft_strlen(s)
			- ft_strlen(ft_strrchr(s, ':')));
	if (!*h)
		*h = new_node;
	else
	{
		last_node = *h;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

int	init_tilde(t_home **h)
{
	char	*line;
	int		fd;

	if (!*h)
	{
		fd = open("/etc/passwd", O_RDONLY, 0777);
		if (fd == -1)
			return (perror("Error opening /etc/passwd"), EXIT_FAILURE);
		while (1)
		{
			line = gnhell(fd);
			if (!line)
				break ;
			add_node_h(h, line);
		}
	}
	return (0);
}

char	*home_paths(char *to_find, int token)
{
	static t_home	*h = NULL;
	t_home			*tmp;

	if (token == INIT)
		init_tilde(&h);
	if (token == FIND)
	{
		tmp = h;
		while (tmp)
		{
			if (!ft_strcmp(tmp->dir, to_find))
				return (tmp->path);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

int	is_tilde_in_arr(char **arr, int i, char token)
{
	home_paths(0, INIT);
	if (token == '?')
	{
		while (arr[++i])
		{
			if (arr[i][0] == '~' && arr[i][1])
				if (home_paths(&arr[i][1], FIND))
					return (1);
			else if (arr[i][0] == '~' && !arr[i][1])
				return (1);
		}
	}
	if (token == 'p')
	{
		while (arr[++i])
		{
			if (arr[i][0] == '~' && arr[i][1])
				if (home_paths(&arr[i][1], FIND))
					return (i);
			else if (arr[i][0] == '~' && !arr[i][1])
				return (i);
		}
	}
	return (0);
}

void	get_tilde(char **arr)
{
	int	i;

	i = is_tilde_in_arr(arr, -1, 'p');
	if (arr[i][1] && home_paths(&arr[i][1], FIND))
		arr[i] = home_paths(&arr[i][1], FIND);
	else
		arr[i] = ft_strjoin(get_cwdd(0, 0, HOME), &arr[i][1]);
}
