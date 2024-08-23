/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:07:06 by isb3              #+#    #+#             */
/*   Updated: 2024/08/23 12:38:42 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
