/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:44:32 by adesille          #+#    #+#             */
/*   Updated: 2024/08/13 09:54:28 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_exist_exp(t_export *exp, char *var)
{
	char	*exp_var;

	if (ft_strchr(var, '='))
		var = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
						'=')));
	while (exp)
	{
		if (ft_strchr(exp->var, '='))
			exp_var = ft_substr(exp->var, 0, ft_strlen(exp->var)
					- ft_strlen(ft_strchr(exp->var, '=')));
		else
			exp_var = ft_strdup(exp->var);
		if (!ft_strcmp(exp_var, var))
			return (1);
		exp = exp->next;
	}
	return (0);
}

int	cd_utils(char **arr)
{
	if (arr[1] && (!ft_strlen(arr[1]) || !ft_strcmp(arr[1], ".")))
		return (0);
	if (arr[1][0] == '~')
		arr[1] = ft_strjoin(get_cwdd(0, 0, HOME), arr[1] + 1);
	if (!access(arr[1], OK) && access(arr[1], X_OK))
		return (error("Permission denied", "cd", 1));
	get_cwdd(0, arr[1], UPDATE);
	if (!ft_strcmp(arr[1], ".."))
		arr[1] = get_cwdd(0, 0, GET);
	if (chdir(arr[1]))
		return (error("No such file or directory",
				ft_strjoin("cd: ", arr[1]), 1));
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
