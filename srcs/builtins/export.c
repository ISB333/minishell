/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:02:33 by isb3              #+#    #+#             */
/*   Updated: 2024/09/29 09:13:46 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static t_export	*check_if_exist_exp(t_export *exp, const t_string var);
static void		print_export(const t_export *exp_list);
static void		sort_export(t_export *exp_list);
static void		unset_export(t_export **exp_list, t_string var);

/**
 * 📋 Description: manages all actions related to the export command.
 * 
 * @param env: string array representing environment variables.
 * @param var: target variable if requested.
 * @param action: action to perform (INIT, ADD, PRINT, UNSET).
 *
 * ⬅️ Return: nothing.
 */
void	exportt(const t_string var, const int action)
{
	static t_export	*exp_list = NULL;

	if (action == INIT)
		init_export(get_envv(NULL, NULL, GET), &exp_list);
	else if (action == ADD && var)
	{
		if (!get_envv(NULL, var, ADD) && is_valid_env_var(var)
			&& !check_if_exist_exp(exp_list, var))
		{
			add_node_exp(&exp_list, var);
			sort_export(exp_list);
		}
		else if (!is_valid_env_var(var))
			error("not a valid identifier", ft_strjoin("export: ", var), 1);
		else
			modify_exp_var(exp_list, var);
	}
	else if (action == PRINT)
		print_export(exp_list);
	else if (action == UNSET && var)
		unset_export(&exp_list, var);
}

/**
 * 📋 Description: checks if an export variable exists in the list.
 * 
 * @param exp: list of export variables.
 * @param var: variable to check for existence.
 *
 * ⬅️ Return: t_export *, a pointer to the variable if existing.
 */
static t_export	*check_if_exist_exp(t_export *exp, const t_string var)
{
	t_string	current_var;
	t_string	var_to_check;

	if (!exp || !var)
		return (NULL);
	if (ft_strchr(var, '+'))
		var_to_check = ft_substr(var, 0, ft_strchr(var, '+') - var);
	else if (ft_strchr(var, '='))
		var_to_check = ft_substr(var, 0, ft_strchr(var, '=') - var);
	else
		var_to_check = ft_strdup(var);
	while (exp)
	{
		if (ft_strchr(exp->var, '='))
			current_var = ft_substr(exp->var, 0, ft_strchr(exp->var, '=')
					- exp->var);
		else
			current_var = ft_strdup(exp->var);
		if (ft_strcmp(current_var, var_to_check) == EQUAL)
			return (exp);
		exp = exp->next;
	}
	return (NULL);
}

/**
 * 📋 Description: displays all export variables in the terminal.
 * 
 * @param exp: list of export variables.
 *
 * ⬅️ Return: nothing.
 */
static void	print_export(const t_export *exp_list)
{
	while (exp_list)
	{
		printf("declare -x %s\n", exp_list->var);
		exp_list = exp_list->next;
	}
}

/**
 * 📋 Description: sorts the list of export variables in ASCII order.
 * 
 * @param export_list: list of export variables.
 *
 * ⬅️ Return: nothing.
 */
static void	sort_export(t_export *export_list)
{
	t_string	tmp;
	t_export	*outer;
	t_export	*inner;

	outer = export_list;
	if (!outer)
		return ;
	while (outer->next)
	{
		inner = export_list;
		while (inner && inner->next)
		{
			if (ft_strcmp(inner->var, inner->next->var) > 0)
			{
				tmp = inner->var;
				inner->var = inner->next->var;
				inner->next->var = tmp;
			}
			inner = inner->next;
		}
		outer = outer->next;
	}
}

/**
 * 📋 Description: removes an export variable from the list.
 * 
 * @param exp_list: pointer to the list of export variables.
 * @param var: variable to remove.
 *
 * ⬅️ Return: nothing.
 */
static void	unset_export(t_export **exp_list, t_string var)
{
	t_export	*current;

	if (!exp_list || !var || !*exp_list || ft_strchr(var, '='))
		return ;
	if (ft_strncmp((*exp_list)->var, var, ft_strlen(var)) == EQUAL)
		*exp_list = (*exp_list)->next;
	else
	{
		current = *exp_list;
		while (current->next
			&& ft_strncmp(current->next->var, var, ft_strlen(var)) != EQUAL)
			current = current->next;
		if (current->next)
			current->next = current->next->next;
	}
}
