/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:02:33 by isb3              #+#    #+#             */
/*   Updated: 2024/08/20 08:07:39 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (ft_strcmp(exp->var, exp->next->var) > 0)
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
		printf("declare -x %s\n", exp->var);
		exp = exp->next;
	}
}

int	check_if_exist_exp(t_export *exp, char *var)
{
	char	*exp_var;

	if (ft_strchr(var, '='))
		var = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
						'=')));
	while (exp)
	{
		if (ft_strchr(exp->var, '='))
			exp_var = ft_substr(exp->var, 0, ft_strlen(exp->var)
					- ft_strlen(ft_strchr(exp->var, '=')));
		else
			exp_var = ft_strdup(exp->var);
		if (!ft_strcmp(exp_var, var))
			return (1);
		exp = exp->next;
	}
	return (0);
}

void	unset_export(t_export **exp, char *var)
{
	t_export	*tmp;

	if (!var)
		return ;
	tmp = *exp;
	if (!ft_strncmp((*exp)->var, var, ft_strlen(var)))
		*exp = (*exp)->next;
	else
	{
		while (tmp)
		{
			if (tmp->next && !ft_strncmp(tmp->next->var, var, ft_strlen(var)))
			{
				tmp->next = tmp->next->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

void	exportt(char *env[], char *var, int token)
{
	static t_export	*exp;

	if (token == INIT)
		init_export(env, &exp);
	if (token == ADD)
	{
		if (!var)
			return ;
		if (!get_envv(0, var, ADD) && env_format_check(var)
			&& !check_if_exist_exp(exp, var))
		{
			add_node_exp(&exp, var);
			sort_export(exp);
		}
		else if (!env_format_check(var))
			error("not a valid identifier", ft_strjoin("export: ", var), 1);
		else
			modify_exp_var(exp, var);
	}
	if (token == PRINT)
		print_export(exp);
	if (token == UNSET)
		unset_export(&exp, var);
}
