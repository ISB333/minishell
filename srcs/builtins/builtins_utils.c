/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:20:22 by isb3              #+#    #+#             */
/*   Updated: 2024/08/27 17:30:06 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: checks if an argument consists entirely of 'n' characters.
 * 
 * @param arg: the argument passed to echo.
 *
 * ⬅️ Return: t_bool, TRUE if only 'n' characters, FALSE otherwise.
 */
t_bool	is_only_n(t_string arg)
{
	if (!arg)
		return (FALSE);
	while (*++arg == 'n')
		continue ;
	return (!*arg);
}

/**
 * 📋 Description: handles the cd command's action after initial checks.
 * 
 * @param args: the arguments passed to cd.
 *
 * ⬅️ Return: int, the error code or 0 on success.
 */
int	cd_utils(t_string *args)
{
	if (args[1] && (!ft_strlen(args[1]) || ft_strcmp(args[1], ".")) == EQUAL)
		return (0);
	if (*args[1] == '~')
		args[1] = ft_strjoin(get_cwdd(NULL, NULL, HOME), args[1] + 1);
	if (access(args[1], OK) == EXIT_SUCCESS
		&& access(args[1], X_OK) != EXIT_SUCCESS)
		return (error("Permission denied", "cd", 1));
	if (ft_strcmp(args[1], "..") == EQUAL)
	{
		exportt(NULL, ft_strjoin("OLDPWD=", get_cwdd(NULL, NULL, GET)), ADD);
		get_cwdd(NULL, args[1], UPDATE);
		args[1] = get_cwdd(NULL, NULL, GET);
		exportt(NULL, ft_strjoin("PWD=", get_cwdd(NULL, NULL, GET)), ADD);
	}
	else
	{
		exportt(NULL, ft_strjoin("OLDPWD=", get_cwdd(NULL, NULL, GET)), ADD);
		get_cwdd(NULL, args[1], UPDATE);
		exportt(NULL, ft_strjoin("PWD=", get_cwdd(NULL, NULL, GET)), ADD);
	}
	if (chdir(args[1]))
		return (error("No such file or directory", ft_strjoin("cd: ",
					args[1]), 1));
	return (0);
}

/**
 * 📋 Description: cleans up and exits minishell with the given status code.
 * 
 * @param status: the exit status code.
 *
 * ⬅️ Return: nothing.
 */
void	quit(int status)
{
	if (status < 0)
		status = EXIT_FAILURE;
	mem_manager(0, NULL, 0, CLEAR_MEMORY);
	exit(status);
}

/**
 * 📋 Description: counts the number of directories in the given path.
 * 
 * @param path: the path to analyze.
 *
 * ⬅️ Return: size_t, the number of directories in the path.
 */
size_t	count_dir(t_string path)
{
	size_t	count;

	count = 0;
	if (path)
	{
		while (*path)
		{
			if (*path == '/')
			{
				while (*path == '/')
					++path;
				++count;
			}
			else
				++path;
		}
		++count;
	}
	return (count);
}
