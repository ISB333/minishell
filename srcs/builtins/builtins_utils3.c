/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:34:06 by isb3              #+#    #+#             */
/*   Updated: 2024/08/19 12:59:41 by isb3             ###   ########.fr       */
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
	// int	i;

	// i = 0;
	// while (s[++i])
	// {
	// 	if (s[i] != 'n')
	// 		return (0);
	// }
	// return (1);
	while (++s)
		if (*s != 'n')
			break ;
	return (*s != 'n');
}

int	modify_exp_var(t_export *exp, char *var)
{
	char	*exp_var;
	char 	*var_to_modif;

	var_to_modif = ft_substr(var, 0, ft_strlen(var)
			- ft_strlen(ft_strchr(var, '=')));
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

int	call_builtins(t_ast *ast, int c, int token)
{
	int	return_code;
	int	i;

	i = 0;
	return_code = 0;
	if (c == CD)
		return_code = cd(ast->cmd);
	if (c == PWD)
		pwdd();
	if (c == ECH)
		echoo(ast->cmd);
	if (c == EXPORT && !ast->cmd[1])
		exportt(0, 0, PRINT);
	while (c == EXPORT && ast->cmd[i])
		exportt(0, ast->cmd[++i], ADD);
	if (c == ENV)
		get_envv(0, 0, PRINT);
	while (c == UNSET && ast->cmd[i])
	{
		exportt(0, ast->cmd[++i], UNSET);
		get_envv(0, ast->cmd[i], UNSET);
	}
	if (token == EXIT)
		quit(EXIT_SUCCESS);
	return (return_code);
}
