/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:07:06 by isb3              #+#    #+#             */
/*   Updated: 2024/08/23 09:00:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: modifies the value of an existing export variable.
 * 
 * @param export_list: the list of all export variables.
 * @param var: the variable to replace.
 *
 * ⬅️ Return: nothing.
 */
void	modify_exp_var(t_export *export_list, const t_string var)
{
	t_string		exp_var;
	const t_string	var_to_modif = ft_substr(var, 0, ft_strchr(var, '=') - var);

	if (!var_to_modif || !ft_strchr(var, '='))
		return ;
	while (export_list)
	{
		if (ft_strchr(export_list->var, '='))
			exp_var = ft_substr(export_list->var, 0,
					ft_strchr(export_list->var, '=') - export_list->var);
		else
			exp_var = ft_strdup(export_list->var);
		if (ft_strcmp(exp_var, var_to_modif) == EQUAL)
			export_list->var = ft_strdup(var);
		export_list = export_list->next;
	}
}

/**
 * 📋 Description: sorts and stores environment variables as exports.
 * 
 * @param env: the list of all environment variables.
 * @param export_list: the address of the list where to store the variables.
 *
 * ⬅️ Return: nothing.
 */
void	init_export(t_string env[], t_export **export_list)
{
	t_string	tmp;
	size_t		index;
	size_t		scan;

	index = 0;
	if (!env || !*env || !export_list)
		return ;
	while (env[index + 1])
	{
		scan = 0;
		while (env[scan + 1])
		{
			if (ft_strcmp(env[scan], env[scan + 1]) > 0)
			{
				tmp = env[scan];
				env[scan] = env[scan + 1];
				env[scan + 1] = tmp;
			}
			++scan;
		}
		++index;
	}
	while (*env)
		add_node_exp(export_list, *env++);
}

/**
 * 📋 Description: adds a variable to the export list and sorts it.
 * 
 * @param exp_list: the list of all export variables.
 * @param var: the variable to add.
 *
 * ⬅️ Return: nothing.
 */
void	add_node_exp(t_export **exp_list, const t_string var)
{
	t_export	*new_node;

	if (!exp_list || !var)
		return ;
	new_node = mem_manager(sizeof(t_export), 0, 0, ALLOCATE);
	new_node->var = ft_strdup(var);
	new_node->next = NULL;
	if (!*exp_list)
		*exp_list = new_node;
	else
		((t_export *)get_node_at(*exp_list, LAST))->next = new_node;
}
