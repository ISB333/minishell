/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh_in_arr2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 06:23:29 by isb3              #+#    #+#             */
/*   Updated: 2024/07/04 09:40:45 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_del(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		else
			break ;
	}
	if (!s[i])
		return (1);
	return (0);
}

int	is_pipe_in_arr(char **array)
{
	int	i;
	int	k;
	int	n;

	i = -1;
	n = 0;
	while (array[++i])
	{
		k = -1;
		while (array[i][++k])
		{
			if (array[i][k] == '|' && array[i + 1])
				n++;
		}
	}
	return (n);
}

int	is_new_line_in_arr(char **array)
{
	int	i;
	int	k;
	int	n;

	i = -1;
	n = 0;
	while (array[++i])
	{
		k = -1;
		while (array[i][++k])
		{
			if (array[i][k] == '\n' && array[i - 1][0] != '|')
				n++;
		}
	}
	return (n);
}

int	is_redir_in_arr(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (0);
	while (array[++i])
	{
		if (array[i][0] == '<')
			return (1);
		if (array[i][0] == '>')
			return (2);
	}
	return (0);
}

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
		return (1);
	return (0);
}
