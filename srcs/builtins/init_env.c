/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:43:50 by aheitz            #+#    #+#             */
/*   Updated: 2024/09/30 09:12:22 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: initializes the environment variables if they do not exist.
 *
 * @param env: the array of strings representing environment variables.
 * @param env_head: the list where the environment variables will be stored.
 *
 * ⬅️ Return: nothing.
 */
void	init_env(t_string env[], t_env **env_head)
{
	t_string	cwd;

	if (!env_head || !env)
		return ;
	if (!*env)
	{
		env = mem_manager(4 * sizeof(t_string), NULL, 0, ALLOCATE);
		cwd = getcwd(NULL, 0);
		env[0] = ft_strjoin("PWD=", cwd);
		free(cwd);
		env[1] = ft_strdup("SHLVL=1");
		env[2] = ft_strjoin("PATH=/usr/local/sbin:/usr/local/bin",
				":/usr/sbin:/usr/bin:/sbin:/bin");
		env[3] = NULL;
	}
	while (*env)
	{
		if (!ft_strncmp(*env, "SHLVL=", 6))
			*env = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(ft_strchr(*env, '=')
							+ 1) + 1));
		add_env_var(env_head, *env++);
	}
}
