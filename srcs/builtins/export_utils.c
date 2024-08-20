/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:07:06 by isb3              #+#    #+#             */
/*   Updated: 2024/08/20 08:55:14 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modify_exp_var(t_export *exp, char *var)
{
	char	*exp_var;
	char	*var_to_modif;

	var_to_modif = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
					'=')));
	while (exp)
	{
		if (ft_strchr(exp->var, '='))
			exp_var = ft_substr(exp->var, 0, ft_strlen(exp->var)
					- ft_strlen(ft_strchr(exp->var, '=')));
		else
			exp_var = ft_strdup(exp->var);
		if (!ft_strcmp(exp_var, var_to_modif))
		{
			if (ft_strrchr(var, '='))
				exp->var = ft_strdup(var);
			return (0);
		}
		exp = exp->next;
	}
	return (1);
}

void	add_node_exp(t_export **exp, char *var)
{
	t_export	*new_node;
	t_export	*last_node;

	new_node = mem_manager(sizeof(t_export), 0, 0, 'A');
	new_node->var = ft_strdup(var);
	new_node->next = NULL;
	if (!*exp)
		*exp = new_node;
	else
	{
		last_node = *exp;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

void	init_export(char *env[], t_export **exp)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	i = -1;
	len = array_len(env);
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - 1 - i)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = ft_strdup(env[j]);
				env[j] = ft_strdup(env[j + 1]);
				env[j + 1] = ft_strdup(temp);
			}
		}
	}
	i = -1;
	while (env && env[++i])
		add_node_exp(exp, env[i]);
}

int	lst_len(t_export *exp)
{
	int	len;

	len = 0;
	while (exp)
	{
		len++;
		exp = exp->next;
	}
	return (len);
}
