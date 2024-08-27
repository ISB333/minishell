/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:20:22 by isb3              #+#    #+#             */
/*   Updated: 2024/08/27 13:56:14 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_n(char *s)
{
	while (*++s == 'n')
		;
	return (!*s);
}

int	cd_utils(char **arr)
{
	if (arr[1] && (!ft_strlen(arr[1]) || !ft_strcmp(arr[1], ".")))
		return (0);
	if (arr[1][0] == '~')
		arr[1] = ft_strjoin(get_cwdd(0, 0, HOME), arr[1] + 1);
	if (!access(arr[1], OK) && access(arr[1], X_OK))
		return (error("Permission denied", "cd", 1));
	exportt(0, ft_strjoin("OLDPWD=", get_cwdd(0, 0, GET)), ADD);
	if (!ft_strcmp(arr[1], ".."))
	{
		get_cwdd(0, arr[1], UPDATE);
		arr[1] = get_cwdd(0, 0, GET);
		if (chdir(arr[1]))
			return (error("No such file or directory", ft_strjoin("cd: ",
						arr[1]), 1));
	}
	else
	{
		if (chdir(arr[1]))
			return (error("No such file or directory", ft_strjoin("cd: ",
						arr[1]), 1));
		get_cwdd(0, arr[1], UPDATE);
	}
	exportt(0, ft_strjoin("PWD=", get_cwdd(0, 0, GET)), ADD);
	return (0);
}

int	quit(int token)
{
	if (token == EXIT_FAILURE)
	{
		mem_manager(0, 0, 0, CLEAR_MEMORY);
		exit(EXIT_FAILURE);
	}
	if (token == EXIT_SUCCESS)
	{
		mem_manager(0, 0, 0, CLEAR_MEMORY);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	count_dir(char *cwd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!cwd)
		return (0);
	while (cwd[i])
	{
		if (cwd[i] == '/' && cwd[i + 1] == '/')
			i++;
		if (cwd[i] == '/' || !cwd[i + 1])
			len++;
		i++;
	}
	return (len);
}
