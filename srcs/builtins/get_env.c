/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:31:58 by adesille          #+#    #+#             */
/*   Updated: 2024/07/06 06:32:40 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_env(t_env **envv, char *var)
{
	t_env	*new_node;
	t_env	*last_node;

	new_node = mem_manager(sizeof(t_env), 0, 0, 'A');
	new_node->var = ft_strdup(var);
	new_node->next = NULL;
	if (!*envv)
		*envv = new_node;
	else
	{
		last_node = *envv;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

char	*env_var_search(t_env *envv, char *to_find)
{
	while (envv)
	{
		if (!ft_strncmp(envv->var, to_find, ft_strlen(to_find)))
			return (ft_strchr(envv->var, '=') + 1);
		envv = envv->next;
	}
	return (NULL);
}

char	*get_envv(char *env[], char *to_find, int token)
{
	static	t_env	*envv;
	int				i;

	if (token == 'I')
	{
		i = -1;
		while (env[++i])
			add_node_env(&envv, env[i]);
	}
	if (token == 'F')
		return (env_var_search(envv, to_find));
	return (NULL);
}
