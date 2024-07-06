/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:31:58 by adesille          #+#    #+#             */
/*   Updated: 2024/07/06 15:52:53by isb3             ###   ########.fr       */
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

void	print_env(t_env *envv)
{
	while (envv)
	{
		printf("%s\n", envv->var);
		envv = envv->next;
	}
}

void	unset_env(t_env **envv, char *var)
{
	t_env	*prev;
	t_env	*curr;

	prev = *envv;
	curr = *envv;
	if (!ft_strncmp((*envv)->var, var, ft_strlen(var)))
		*envv = (*envv)->next;
	else
	{
		prev = curr;
		curr = curr->next;
		while (curr)
		{
			if (!ft_strncmp(curr->var, var, ft_strlen(var)))
			{
				prev->next = curr->next;
				return ;
			}
			prev = curr;
			curr = curr->next;
		}
	}
}

void	modify_env_var(t_env *envv, char *var)
{
	char	*envv_var;

	while (envv)
	{
		envv_var = ft_substr(envv->var, 0, ft_strlen(envv->var)
				- ft_strlen(ft_strchr(envv->var, '=')));
		if (!ft_strncmp(envv->var, var, ft_strlen(envv_var)))
		{
			envv->var = ft_strdup(var);
			return ;
		}
		envv = envv->next;
	}
}

int	check_if_exist(t_env *envv, char *var)
{
	char	*envv_var;

	if (ft_strchr(var, '='))
		var = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
						'=')));
	while (envv)
	{
		if (ft_strchr(envv->var, '='))
			envv_var = ft_substr(envv->var, 0, ft_strlen(envv->var)
					- ft_strlen(ft_strchr(envv->var, '=')));
		else
			envv_var = ft_strdup(envv->var);
		if (!ft_strncmp(envv->var, var, ft_strlen(envv_var)))
			return (1);
		envv = envv->next;
	}
	return (0);
}

char	*get_envv(char *env[], char *var, int token)
{
	static t_env	*envv;
	int				i;

	if (token == 'I')
	{
		i = -1;
		while (env[++i])
			add_node_env(&envv, env[i]);
	}
	if (token == 'A')
	{
		if (!check_if_exist(envv, var))
		{
			printf("notexisting\n");
			add_node_env(&envv, var);
			return (NULL);
		}
		else
		{
			printf("exist\n");
			get_envv(0, var, 'M');
			return ("YES");
		}
	}
	if (token == 'U')
		unset_env(&envv, var);
	if (token == 'F')
		return (env_var_search(envv, var));
	if (token == 'M')
		modify_env_var(envv, var);
	if (token == 'P')
		print_env(envv);
	return (NULL);
}
