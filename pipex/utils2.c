/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:44:32 by adesille          #+#    #+#             */
/*   Updated: 2024/04/13 16:39:24 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_path(char *env[])
{
	char	**path;
	char	*trimm_path;
	int		i;

	i = 0;
	while (env[i] && (!strstr(env[i], "PATH") || !strstr(env[i], "bin")))
		i++;
	if (!env[i])
		return (NULL);
	trimm_path = ft_strtrim(env[i], "PATH=/");
	if (!trimm_path)
		return (NULL);
	path = ft_split(trimm_path, ':');
	if (!path)
		return (free(trimm_path), NULL);
	return (free(trimm_path), path);
}

char	*path_finder(char *cmd, char *env[])
{
	char	**path;
	char	**full_cmd;
	char	*test_path;
	int		i;

	path = extract_path(env);
	if (!path)
		return (NULL);
	i = -1;
	full_cmd = ft_split(cmd, ' ');
	if (!full_cmd)
		return (free_memory(path), NULL);
	cmd = ft_strjoin("/", full_cmd[0]);
	if (!cmd)
		return (free(full_cmd), free_memory(path), NULL);
	free_memory(full_cmd);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
			return (free(cmd), free_memory(path), test_path);
		free(test_path);
	}
	return (free(cmd), free_memory(path), ft_substr("notexisting", 0, 3));
}

char	**get_cmd_path(char *argv[], char *env[])
{
	char	**cmd_paths;
	int		i;
	int		k;

	i = 2;
	while (argv[i])
		i++;
	cmd_paths = malloc((i - 2) * sizeof(char *));
	if (!cmd_paths)
		return (NULL);
	cmd_paths[i - 3] = NULL;
	k = 0;
	i = 2;
	while (argv[i + 1])
	{
		cmd_paths[k] = path_finder(argv[i++], env);
		if (!cmd_paths[k++])
			return (free_memory(cmd_paths), \
				ft_putstr_fd("command not found : ", 1), \
				ft_putstr_fd(argv[i - 1], 1), write(1, "\n", 1), NULL);
	}
	return (cmd_paths);
}

int	format_check(char *argv[])
{
	int	i;

	i = 0;
	while (argv[++i + 1])
	{
		if (argv[i][0] == '-')
			return (-1);
	}
	return (0);
}
