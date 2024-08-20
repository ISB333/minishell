/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 06:55:48 by isb3              #+#    #+#             */
/*   Updated: 2024/08/20 06:56:00 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_ast *ast)
{
	if (!ast || !ast->cmd)
		return (0);
	if (!ft_strcmp(ast->cmd[0], "cd"))
		return (CD);
	if (!ft_strcmp(ast->cmd[0], "pwd"))
		return (PWD);
	if (!ft_strcmp(ast->cmd[0], "export"))
		return (EXPORT);
	if (!ft_strcmp(ast->cmd[0], "unset"))
		return (UNSET);
	if (!ft_strcmp(ast->cmd[0], "env"))
		return (ENV);
	if (!ft_strcmp(ast->cmd[0], "echo"))
		return (ECH);
	if (!ft_strcmp(ast->cmd[0], "exit"))
		return (EXIT);
	return (0);
}
