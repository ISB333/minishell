/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:02:33 by isb3              #+#    #+#             */
/*   Updated: 2024/09/29 11:39:59 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static size_t	calculate_env_list_length(t_env *env_list, const int action);

/**
 * 📋 Description: checks if a variable name is lexically valid.
 * 
 * @param var: the variable name to validate.
 *
 * ⬅️ Return: t_bool, TRUE if the variable name is valid, FALSE otherwise.
 */
t_bool	is_valid_env_var(t_string var)
{
	if (var && ft_isalpha(*var))
	{
		while (*var && (ft_isalnum(*var) || *var == '_'))
			++var;
		if (!*var || *var == '=' || (*var == '+' && *(var + 1) == '='))
			return (TRUE);
	}
	return (FALSE);
}

/**
 * 📋 Description: searches for the value of a given environment variable.
 * 
 * @param env_list: the list containing all the environment variables.
 * @param to_find: the target variable name.
 *
 * ⬅️ Return: t_string, the value of the target variable, or NULL if not found.
 */
t_string	find_env_var_value(t_env *env, const t_string to_find)
{
	const size_t	len = ft_strlen(to_find);
	t_string		equal_sign;

	if (env && to_find)
	{
		while (env)
		{
			equal_sign = ft_strchr(env->var, '=');
			if (equal_sign
				&& ft_strncmp(env->var, to_find, ft_strlen(to_find)) == EQUAL
				&& env->var[len] == '=')
				return (equal_sign + 1);
			env = env->next;
		}
	}
	return (NULL);
}

/**
 * 📋 Description: retrieves or prints the environment variables.
 * 
 * @param env_list: the list containing all the environment variables.
 * @param action: the action to perform (GET or PRINT).
 *
 * ⬅️ Return: t_string *, a list of environment variables if GET is specified.
 */
t_string	*retrieve_or_display_env(t_env *env_list, const int action)
{
	t_string	*env_array;
	t_string	*env_array_start;
	size_t		length;

	if (!env_list)
		return (NULL);
	length = calculate_env_list_length(env_list, action);
	if (action == GET)
	{
		env_array = mem_manager((length + 1) * sizeof(t_string),
				NULL, 0, ALLOCATE);
		env_array[length] = NULL;
		env_array_start = env_array;
		while (env_list)
		{
			*env_array++ = env_list->var;
			env_list = env_list->next;
		}
		return (env_array_start);
	}
	return (NULL);
}

/**
 * 📋 Description: calculates length of the environment and optionally prints it.
 * 
 * @param env_list: the list containing all the environment variables.
 * @param action: the action to perform (PRINT or GET).
 *
 * ⬅️ Return: size_t, the number of environment variables.
 */
static size_t	calculate_env_list_length(t_env *env_list, const int action)
{
	size_t	length;

	length = 0;
	while (env_list)
	{
		if (action == PRINT)
			printf("%s\n", env_list->var);
		++length;
		env_list = env_list->next;
	}
	return (length);
}
