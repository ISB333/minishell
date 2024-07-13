/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:34:06 by isb3              #+#    #+#             */
/*   Updated: 2024/07/13 06:14:31 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_format_check(char *var)
{
	int	i;

	i = -1;
	if (!ft_isalpha(var[0]))
		return (0);
	while (var[++i] && var[i] != '=')
		if (var[i] != '=' && !ft_isalnum(var[i]))
			return (0);
	return (1);
}

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

int	call_builtins(t_ast *ast, int c, int token)
{
	int	return_code;

	return_code = 0;
	if (c == CD)
		return_code = cd(ast->cmd);
	if (c == PWD)
		pwdd();
	if (c == ECH)
		echoo(ast->cmd);
	if (c == EXPORT && !ast->cmd[1])
		exportt(0, 0, PRINT);
	if (c == EXPORT && ast->cmd[1])
		exportt(0, ast->cmd[1], ADD);
	if (c == ENV)
		get_envv(0, 0, PRINT);
	if (c == UNSET)
	{
		exportt(0, ast->cmd[1], UNSET);
		get_envv(0, ast->cmd[1], UNSET);
	}
	if (token == EXIT)
		quit(EXIT_SUCCESS);
	return (return_code);
}
