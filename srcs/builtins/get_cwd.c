/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:32:54 by adesille          #+#    #+#             */
/*   Updated: 2024/07/15 13:42:01 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_cwd(t_cwd **cwdd, char *dirr)
{
	t_cwd	*new_node;
	t_cwd	*last_node;

	new_node = mem_manager(sizeof(t_cwd), 0, 0, 'A');
	new_node->dir = ft_strdup(dirr);
	new_node->next = NULL;
	if (!*cwdd)
		*cwdd = new_node;
	else
	{
		last_node = *cwdd;
		while (last_node->next)
			last_node = last_node->next;
		if (last_node->dir[ft_strlen(last_node->dir) - 1] != '/')
			last_node->dir = ft_strjoin(last_node->dir, "/");
		last_node->next = new_node;
	}
}

char	**split_cwd(char *cwd)
{
	char	**cwd_dir;
	int		len;
	int		i;
	int		k;
	int		j;

	len = 0;
	i = 0;
	k = 0;
	j = 0;
	len = count_dir(cwd);
	cwd_dir = mem_manager((len + 1) * sizeof(char *), 0, 0, 'A');
	cwd_dir[len] = NULL;
	while (cwd[i])
	{
		if (cwd[i] == '/' || !cwd[i + 1])
		{
			cwd_dir[j++] = ft_substr(cwd, k, i - k + 1);
			k = ++i;
		}
		else
			i++;
	}
	return (cwd_dir);
}

void	update_cwd(t_cwd **cwdd, char *new_dir)
{
	t_cwd	*last_node;

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
	{
		last_node = *cwdd;
		while (last_node->next && last_node->next->next)
			last_node = last_node->next;
		if (!ft_strcmp(new_dir, ".."))
		{
			if (last_node->dir[0] == '/' && last_node->next)
				last_node->next = NULL;
			else if (last_node->dir[0] != '/')
				last_node->next = NULL;
		}
		else
			add_node_cwd(cwdd, new_dir);
	}
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
		cwd_dir = split_cwd(cwd);
		i = -1;
		while (cwd_dir[++i])
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
