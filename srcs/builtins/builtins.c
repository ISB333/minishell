/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:41:47 by adesille          #+#    #+#             */
/*   Updated: 2024/08/21 14:26:09 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echoo(char **arr)
{
	int	i;
	int	token;

	token = 0;
	i = 0;
	while (arr[++i] && !ft_strncmp(arr[i], "-n", 2))
	{
		if (is_only_n(arr[i]))
			token = 1;
		else
			break ;
	}
	if (arr[i])
	{
		while (arr[i])
		{
			printf("%s", arr[i]);
			if (arr[++i])
				printf(" ");
		}
		if (!token)
			printf("\n");
	}
	else if (!token)
		printf("\n");
}

void	pwdd(void)
{
	printf("%s\n", get_cwdd(0, 0, GET));
}

int	cd(char **arr)
{
	struct stat	path_stat;
	char		*dir;

	if ((arr[1] && arr[2]))
		return (error("too many arguments", "cd", 1));
	if (arr[1] && ft_strchr(arr[1], '/'))
		dir = ft_substr(arr[1], 0, ft_strlen(arr[1])
				- ft_strlen(ft_strchr(arr[1], '/')));
	else if (arr[1])
		dir = ft_strdup(arr[1]);
	if (!stat(dir, &path_stat) && !S_ISDIR(path_stat.st_mode))
		return (error("Not a directory", ft_strjoin("cd: ", arr[1]), 1));
	if (!arr[1] || !ft_strcmp(arr[1], "~"))
	{
		if (chdir(get_cwdd(0, 0, HOME)))
			return (-1);
		get_cwdd(0, arr[1], UPDATE);
	}
	else
		return (cd_utils(arr));
	return (0);
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
