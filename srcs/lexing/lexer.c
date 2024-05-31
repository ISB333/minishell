/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/05/31 13:31:32 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(char **array)
{
	int	j;

	j = 0;
	if (!array)
		return ;
	while (array[j])
		j++;
	while (j-- > 0)
		free(array[j]);
	free(array);
}

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

char	*get_cmd_path(char *arg, char *env[])
{
	char	*cmd_path;
	int		i;

	i = 2;
	cmd_path = path_finder(arg, env);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

/* e.g:
	while (splitted[i] != PIPE or REDIRECTION etc..)
		parse_cmds_with_args();

	Pipeline
	├── Command: ls
	├── Pipe
	│   └── Command: cat -e
	└── Pipe
		└── Command: ls -la
*/
int	lexer(char *str)
{
	char	**tokens = NULL;
	int		i;

	i = 0;
	tokens = tokenizer(str);
	// cmds_paths = malloc((i + 1) * sizeof(char *));
	// cmds_paths[i] = NULL;
	// i = 0;
	while (tokens[i])
		printf("%s\n", tokens[i++]);
	free_memory(tokens);
	return (0);
}
