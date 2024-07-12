/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:04:31 by adesille          #+#    #+#             */
/*   Updated: 2024/07/12 12:16:52 by isb3             ###   ########.fr       */
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

void	sort_export(t_export *exp)
{
	char		*temp;
	int			len;
	int			i;
	int			j;
	t_export	*origin;

	i = -1;
	len = lst_len(exp);
	origin = exp;
	while (++i < len - 1)
	{
		j = -1;
		exp = origin;
		while (++j < len - 1 - i)
		{
			if (ft_strcmp(ft_strchr(exp->var, 'x') + 2,
					ft_strchr(exp->next->var, 'x') + 2) > 0)
			{
				temp = ft_strdup(exp->var);
				exp->var = ft_strdup(exp->next->var);
				exp->next->var = ft_strdup(temp);
			}
			exp = exp->next;
		}
	}
}

void	print_export(t_export *exp)
{
	while (exp)
	{
		printf("%s\n", exp->var);
		exp = exp->next;
	}
}
