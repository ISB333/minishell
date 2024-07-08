/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:34:06 by isb3              #+#    #+#             */
/*   Updated: 2024/07/08 09:34:35 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_n(char *s)
{
	int	i;

	i = 0;
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

int	modify_exp_var(t_export *exp, char *var)
{
	char	*exp_var;

	while (exp)
	{
		exp_var = ft_strchr(exp->var, 'x') + 2;
		exp_var = ft_substr(exp_var, 0, ft_strlen(exp_var)
				- ft_strlen(ft_strchr(exp_var, '=')));
		if (!ft_strncmp(exp_var, var, ft_strlen(exp_var)))
		{
			exp->var = ft_strjoin("declare -x ", var);
			return (0);
		}
		exp = exp->next;
	}
	return (1);
}
