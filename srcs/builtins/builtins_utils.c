/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:20:22 by isb3              #+#    #+#             */
/*   Updated: 2024/08/22 09:33:41 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_n(char *s)
{
	while (*++s == 'n')
		;
	return (!*s);
}

int	cd_utils(char **arr)
{
	if (arr[1] && (!ft_strlen(arr[1]) || !ft_strcmp(arr[1], ".")))
		return (0);
	if (arr[1][0] == '~')
		arr[1] = ft_strjoin(get_cwdd(0, 0, HOME), arr[1] + 1);
	if (!access(arr[1], OK) && access(arr[1], X_OK))
		return (error("Permission denied", "cd", 1));
	if (!ft_strcmp(arr[1], ".."))
	{
		exportt(0, ft_strjoin("OLDPWD=", get_cwdd(0, 0, GET)), ADD);
		get_cwdd(0, arr[1], UPDATE);
		arr[1] = get_cwdd(0, 0, GET);
		exportt(0, ft_strjoin("PWD=", get_cwdd(0, 0, GET)), ADD);
	}
	else
	{
		exportt(0, ft_strjoin("OLDPWD=", get_cwdd(0, 0, GET)), ADD);
		get_cwdd(0, arr[1], UPDATE);
		exportt(0, ft_strjoin("PWD=", get_cwdd(0, 0, GET)), ADD);
	}
	if (chdir(arr[1]))
		return (error("No such file or directory", ft_strjoin("cd: ",
					arr[1]), 1));
	return (0);
}

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

int	quit(int token)
{
	if (token == EXIT_FAILURE)
	{
		mem_manager(0, 0, 0, 'C');
		exit(EXIT_FAILURE);
	}
	if (token == EXIT_SUCCESS)
	{
		mem_manager(0, 0, 0, 'C');
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	count_dir(char *cwd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!cwd)
		return (0);
	while (cwd[i])
	{
		if (cwd[i] == '/' && cwd[i + 1] == '/')
			i++;
		if (cwd[i] == '/' || !cwd[i + 1])
			len++;
		i++;
	}
	return (len);
}
