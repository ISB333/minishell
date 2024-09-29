/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:31:58 by adesille          #+#    #+#             */
/*   Updated: 2024/09/29 11:56:45 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static void		update_env_var(t_env *env, const t_string var);
static void		remove_env_var(t_env **env_list, const t_string var);
static t_env	*env_var_exists(t_env *env, t_string var);

/**
 * 📋 Description: acts on environment variables depending on the demand.
 *
 * @param env: the list of character strings relating to variables.
 * @param var: the targeted variable when calling the function.
 * @param action: the action to execute (INIT, ADD, UNSET, etc.).
 *
 * ⬅️ Return: NULL for most actions, or a result if applicable.
 */
void	*get_envv(t_string env[], const t_string var, const int action)
{
	static t_env	*env_head = NULL;
	t_env			*existing_var;

	if (action == INIT)
		init_env(env, &env_head);
	else if (action == ADD)
	{
		existing_var = env_var_exists(env_head, var);
		if (!existing_var && is_valid_env_var(var))
			add_env_var(&env_head, var);
		else if (existing_var && is_valid_env_var(var) && ft_strchr(var, '+'))
			return (update_env_var(env_head, var), "MODIF");
		else if (existing_var && is_valid_env_var(var))
			return (existing_var->var = ft_strdup(var), "EXIST");
	}
	else if (action == UNSET)
		remove_env_var(&env_head, var);
	else if (action == FIND)
		return (find_env_var_value(env_head, var));
	else if (action == MODIF)
		update_env_var(env_head, var);
	else if (action == PRINT || action == GET)
		return (retrieve_or_display_env(env_head, action));
	return (NULL);
}

/**
 * 📋 Description: adds an environment variable to the linked list.
 *
 * @param env_list: the address of the environment variable list.
 * @param var: the variable to add to the list.
 *
 * ⬅️ Return: nothing.
 */
void	add_env_var(t_env **env_list, const t_string var)
{
	t_env	*new_node;

	if (!ft_strchr(var, '=') || !env_list)
		return ;
	new_node = mem_manager(sizeof(t_env), 0, 0, ALLOCATE);
	if (ft_strchr(var, '+'))
		new_node->var = ft_strjoin(ft_substr(var, 0, ft_strlen(var)
					- ft_strlen(ft_strrchr(var, '+'))), ft_strchr(var, '='));
	else
		new_node->var = ft_strdup(var);
	new_node->next = NULL;
	if (!*env_list)
		*env_list = new_node;
	else
		((t_env *)get_node_at(*env_list, LAST))->next = new_node;
}

/**
 * 📋 Description: searches for and modifies the targeted variable.
 *
 * @param env: the first variable in the list.
 * @param var: the variable to search for and modify.
 *
 * ⬅️ Return: nothing.
 */
static void	update_env_var(t_env *env, const t_string var)
{
	t_string	cur_key;
	t_string	target_key;

	if (ft_strchr(var, '+'))
		target_key = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
						'=') - 1));
	else
		target_key = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
						'=')));
	if (!target_key)
		return ;
	while (env)
	{
		cur_key = ft_substr(env->var, 0, ft_strlen(env->var)
				- ft_strlen(ft_strchr(env->var, '=')));
		if (ft_strcmp(cur_key, target_key) == EQUAL && ft_strchr(var, '+'))
			return (env->var = ft_strjoin(env->var, ft_strchr(var, '=') + 1),
				(void)0);
		else if (ft_strcmp(cur_key, target_key) == EQUAL)
		{
			env->var = ft_strdup(var);
			return ;
		}
		env = env->next;
	}
}

/**
 * 📋 Description: checks if a variable exists in the list.
 *
 * @param env: the first variable in the list.
 * @param var: the variable to search for in the list.
 *
 * ⬅️ Return: t_env *, pointer to the variable, if eligible.
 */
static t_env	*env_var_exists(t_env *env, t_string var)
{
	t_string	cur_key;

	if (!var)
		return (NULL);
	if (ft_strchr(var, '+'))
		var = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
						'+')));
	else if (ft_strchr(var, '='))
		var = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
						'=')));
	while (env)
	{
		if (ft_strchr(env->var, '='))
			cur_key = ft_substr(env->var, 0, ft_strlen(env->var)
					- ft_strlen(ft_strchr(env->var, '=')));
		else
			cur_key = ft_strdup(env->var);
		if (ft_strcmp(cur_key, var) == EQUAL)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/**
 * 📋 Description: removes a variable from the list.
 *
 * @param env_list: the address of the environment variable list.
 * @param var: the variable to remove from the list.
 *
 * ⬅️ Return: nothing.
 */
static void	remove_env_var(t_env **env_list, const t_string var)
{
	t_env	**prev_next;
	t_env	*cur;

	if (!env_list || !*env_list || !var)
		return ;
	prev_next = env_list;
	cur = *env_list;
	while (cur)
	{
		if (ft_strncmp(cur->var, var, ft_strlen(var)) == EQUAL
			&& cur->var[ft_strlen(var)] == '=')
		{
			*prev_next = cur->next;
			return ;
		}
		prev_next = &cur->next;
		cur = cur->next;
	}
}
