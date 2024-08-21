/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:32:54 by adesille          #+#    #+#             */
/*   Updated: 2024/08/21 14:25:50 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_cwd(char *cwd, int len)
{
	char	**cwd_dir;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	j = -1;
	len = count_dir(cwd);
	cwd_dir = mem_manager((len + 1) * sizeof(char *), 0, 0, 'A');
	cwd_dir[len] = NULL;
	while (cwd[i])
	{
		if (cwd[i] == '/' && cwd[i + 1] == '/')
			i++;
		if (cwd[i] == '/' || !cwd[i + 1])
		{
			cwd_dir[++j] = ft_substr(cwd, k, i - k + 1);
			k = ++i;
		}
		else
			i++;
	}
	return (cwd_dir);
}

void	update_cwd_utils(t_cwd **cwdd, char *new_dir)
{
	t_cwd	*last_node;
	char	**cwd_dir;
	int		i;

	i = -1;
	last_node = *cwdd;
	while (last_node->next && last_node->next->next)
		last_node = last_node->next;
	cwd_dir = split_cwd(new_dir, 0);
	while (cwd_dir[++i] && !ft_strncmp(cwd_dir[i], "..", 2))
	{
		last_node->next = NULL;
		last_node = *cwdd;
		while (last_node->next && last_node->next->next)
			last_node = last_node->next;
	}
	if (cwd_dir[i])
	{
		while (cwd_dir && cwd_dir[i])
			add_node_cwd(cwdd, cwd_dir[i++]);
	}
}

void	update_cwd(t_cwd **cwdd, char *new_dir)
{
	if (!new_dir || !ft_strcmp(new_dir, "~"))
	{
		*cwdd = NULL;
		get_cwdd(get_cwdd(0, 0, HOME), 0, INIT);
	}
	else if (new_dir[0] == '/')
	{
		*cwdd = NULL;
		if (!ft_strcmp(new_dir, "/."))
			get_cwdd("/", 0, INIT);
		else if (!ft_strcmp(new_dir, "//"))
			get_cwdd("//", 0, INIT);
		else
			get_cwdd(new_dir, 0, INIT);
	}
	else
		update_cwd_utils(cwdd, new_dir);
}

char	*join_cwd(t_cwd *cwdd, int i, int k, int len)
{
	t_cwd	*tmp;
	char	*path;

	tmp = cwdd;
	while (tmp)
	{
		len += ft_strlen(tmp->dir);
		if (!tmp->next && tmp->dir[ft_strlen(tmp->dir) - 1] == '/'
			&& tmp->dir[0] != '/')
			len--;
		tmp = tmp->next;
	}
	path = mem_manager(len + 1, 0, 0, 'A');
	while (cwdd)
	{
		i = 0;
		while (cwdd->dir[i])
		{
			if (!cwdd->next && cwdd->dir[i] == '/' && cwdd->dir[0] != '/')
				break ;
			path[k++] = cwdd->dir[i++];
		}
		cwdd = cwdd->next;
	}
	return (path[k] = '\0', path);
}

char	*get_cwdd(char *cwd, char *new_dir, int token)
{
	static t_cwd	*cwdd = NULL;
	static char		*home = NULL;
	char			**cwd_dir;
	int				i;

	if (token == INIT)
	{
		cwd_dir = split_cwd(cwd, 0);
		i = -1;
		while (cwd_dir && cwd_dir[++i])
			add_node_cwd(&cwdd, cwd_dir[i]);
		if (!home)
			home = get_envv(0, "HOME", FIND);
	}
	if (token == UPDATE)
		update_cwd(&cwdd, new_dir);
	if (token == GET)
		return (join_cwd(cwdd, 0, 0, 0));
	if (token == HOME)
		return (home);
	return (NULL);
}
