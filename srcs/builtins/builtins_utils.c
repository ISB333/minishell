/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:04:31 by adesille          #+#    #+#             */
/*   Updated: 2024/07/06 12:09:35 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (env[++i])
		add_node_exp(exp, ft_strjoin("declare -x ", env[i]));
}

void	print_export(t_export *exp)
{
	while (exp)
	{
		printf("%s\n", exp->var);
		exp = exp->next;
	}
}
