/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:31:58 by adesille          #+#    #+#             */
/*   Updated: 2024/08/21 14:44:01 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static void		add_env_var(t_env **env_list, const t_string var);
static void		update_env_var(t_env *env, const t_string var);
static void		remove_env_var(t_env **env_list, const t_string var);
static t_bool	env_var_exists(t_env *env, t_string var);

/**
 * 📋 Description: acts on environment variables depending on the demand.
 * 
 * @param env: the list of character strings relating to variables.
 * @param var: the targeted variable when calling the function.
 * @param action: the action to execute (INIT, ADD, UNSET, etc.).
 *
 * ⬅️ Return: NULL for most actions, or a result if applicable.
 */

void	init_basic_env(char **env[])
{
	*env = mem_manager(4 * sizeof(char *), 0, 0, 'A');
	(*env)[0] = ft_strjoin("PWD=", getcwd(NULL , 0)) ;
	(*env)[1] = ft_strdup("SHLVL=1") ;
	(*env)[2] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	(*env)[3] = NULL;
}

void	*get_envv(t_string env[], const t_string var, const int action)
{
	int				i;
	static t_env	*env_head = NULL;

	if (action == INIT)
	{
		if (!env[0])
			init_basic_env(&env);
		i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			add_env_var(&env_head, env[i++]);
		}
	}
	else if (action == ADD)
	{
		if (!env_var_exists(env_head, var) && env_format_check(var))
			add_env_var(&env_head, var);
		else if (env_format_check(var))
			return (get_envv(0, var, MODIF), "EXIST");
	}
	else if (action == UNSET)
		remove_env_var(&env_head, var);
	else if (action == FIND)
		return (env_var_search(env_head, var));
	else if (action == MODIF)
		update_env_var(env_head, var);
	else if (action == PRINT || action == GET)
		return (print_or_get_env(env_head, action, 0));
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
static void	add_env_var(t_env **env_list, const t_string var)
{
	t_env	*new_node;
	t_env	*last_node;

	if (!ft_strchr(var, '=') || !env_list)
		return ;
	new_node = mem_manager(sizeof(t_env), 0, 0, 'A');
	new_node->var = ft_strdup(var);
	new_node->next = NULL;
	if (!*env_list)
		*env_list = new_node;
	else
	{
		last_node = *env_list;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
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
	t_string		cur_key;
	const t_string	target_key = ft_substr(var, 0, ft_strlen(var)
			- ft_strlen(ft_strchr(var, '=')));

	if (!target_key)
		return ;
	while (env)
	{
		cur_key = ft_substr(env->var, 0, ft_strlen(env->var)
				- ft_strlen(ft_strchr(env->var, '=')));
		if (ft_strcmp(cur_key, target_key) == EQUAL)
		{
			if (ft_strrchr(var, '='))
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
 * ⬅️ Return: t_bool, indicating the existence of the variable.
 */
static t_bool	env_var_exists(t_env *env, t_string var)
{
	t_string	cur_key;

	if (!var)
		return (FALSE);
	if (ft_strchr(var, '='))
		var = ft_substr(var, 0, ft_strlen(var)
				- ft_strlen(ft_strchr(var, '=')));
	while (env)
	{
		if (ft_strchr(env->var, '='))
			cur_key = ft_substr(env->var, 0, ft_strlen(env->var)
					- ft_strlen(ft_strchr(env->var, '=')));
		else
			cur_key = ft_strdup(env->var);
		if (ft_strcmp(cur_key, var) == EQUAL)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
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
