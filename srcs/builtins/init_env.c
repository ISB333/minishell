/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:43:50 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/23 12:55:31 by aheitz           ###   ########.fr       */
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
	if (!env_head || ! env)
		return ;
	if (!*env)
	{
		env = mem_manager(4 * sizeof(t_string), NULL, 0, ALLOCATE);
		env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		env[1] = ft_strdup("SHLVL=1");
		env[2] = ft_strjoin("PATH=/usr/local/sbin:/usr/local/bin",
				":/usr/sbin:/usr/bin:/sbin:/bin");
		env[3] = NULL;
	}
	while (*env)
		add_env_var(env_head, *env++);
}
