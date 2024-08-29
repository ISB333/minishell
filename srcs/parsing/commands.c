/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:54:09 by isb3              #+#    #+#             */
/*   Updated: 2024/08/29 12:52:24 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_directory_utils(t_ast **ast)
{
	if ((access((*ast)->cmd[0], R_OK) || access((*ast)->cmd[0], X_OK))
		&& !ft_strncmp((*ast)->cmd[0], "./", 2))
	{
		(*ast)->error = error_init("Permission denied", (*ast)->cmd[0]);
		(*ast)->error_code = 126;
		return (return_(126, ADD), 126);
	}
	if (!access((*ast)->cmd[0], X_OK) && ((*ast)->cmd[0][0] == '.'
		|| (*ast)->cmd[0][0] == '/'))
	{
		(*ast)->cmd_path = ft_strdup((*ast)->cmd[0]);
		return (0);
	}
	else
	{
		(*ast)->error = error_init("command not found", (*ast)->cmd[0]);
		(*ast)->error_code = 127;
		return (return_(127, ADD), 127);
	}
	return (0);
}

int	check_if_directory(t_ast **ast)
{
	struct stat	path_stat;

	if (stat((*ast)->cmd[0], &path_stat) != 0 && (!ft_strncmp((*ast)->cmd[0],
				"./", 2) || (*ast)->cmd[0][0] == '/') && access((*ast)->cmd[0],
			OK))
	{
		(*ast)->error = error_init("No such file or directory", (*ast)->cmd[0]);
		(*ast)->error_code = 127;
		return (return_(127, ADD), 127);
	}
	if ((!ft_strncmp((*ast)->cmd[0], "/", 1) || !ft_strncmp((*ast)->cmd[0],
				"./", 2)) && S_ISDIR(path_stat.st_mode))
	{
		(*ast)->error = error_init("Is a directory", (*ast)->cmd[0]);
		(*ast)->error_code = 126;
		return (return_(126, ADD), 126);
	}
	else
		return (check_if_directory_utils(ast));
	return (0);
}

char	**extract_path(void)
{
	char	**path;
	char	*trimm_path;

	trimm_path = get_envv(0, "PATH", FIND);
	if (!trimm_path)
		return (NULL);
	path = ft_split(trimm_path, ':');
	return (path);
}

int	cmd_path_init(t_ast **ast, int i)
{
	char	**path;
	char	*cmd;
	char	*test_path;

	if ((*ast)->cmd == NULL || (*ast)->cmd[0] == NULL || is_builtin(*ast))
		return (0);
	if (!ft_strlen((*ast)->cmd[0]))
		return (check_if_directory(ast));
	path = extract_path();
	if (!path)
	{
		(*ast)->error = error_init("No such file or directory", (*ast)->cmd[0]);
		return ((*ast)->cmd = NULL, return_(127, ADD), 127);
	}
	cmd = ft_strjoin("/", (*ast)->cmd[0]);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
		{
			(*ast)->cmd_path = test_path;
			return (return_(0, ADD), 0);
		}
	}
	return (check_if_directory(ast));
}

int	parse_cmd(t_ast **ast, char **tok, int *i, int j)
{
	int	k;

	k = *i;
	(*ast)->cmd = mem_manager((cmdlen(tok, i) + 1) * sizeof(char *), 0, 0,
			ALLOCATE);
	if (!(*ast)->cmd)
		return (1);
	while (tok[k] && !is_pipe(tok[k], 0, 0))
	{
		if (is_redir(tok[k], 0, 0) || is_append(tok[k], 0, 0)
			|| is_heredoc(tok[k], 0, 0))
			k += 2;
		else if (is_there_quotes_in_da_shit(tok[k]) && tok[k])
			(*ast)->cmd[++j] = quotes_destroyer(tok[k++], 0, 0, 0);
		else if (!ft_strlen(tok[k]))
			k++;
		else if (!is_pipe(tok[k], 0, 0))
		{
			(*ast)->cmd[++j] = ft_substr(tok[k], 0, ft_strlen(tok[k]));
			k++;
		}
		if (!(*ast)->cmd[j])
			return (1);
	}
	return ((*ast)->cmd[++j] = NULL, 0);
}
