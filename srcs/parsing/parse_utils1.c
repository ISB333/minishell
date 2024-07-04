/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:33 by adesille          #+#    #+#             */
/*   Updated: 2024/07/04 09:44:39 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_directory(t_ast **ast)
{
	struct stat	path_stat;

	if (stat((*ast)->cmd[0], &path_stat) != 0 && access((*ast)->cmd[0], OK))
	{
		(*ast)->error = error_init("No such file or directory", (*ast)->cmd[0]);
		return ((*ast)->cmd = NULL, g_error_code = 127, 127);
	}
	if (((*ast)->cmd[0][0] == '.' && S_ISDIR(path_stat.st_mode))
		|| ((*ast)->cmd[0][0] == '/' && S_ISDIR(path_stat.st_mode)))
	{
		(*ast)->error = error_init("Is a directory", (*ast)->cmd[0]);
		return ((*ast)->cmd = NULL, g_error_code = 126, 126);
	}
	if (access((*ast)->cmd[0], R_OK) || access((*ast)->cmd[0], X_OK))
	{
		(*ast)->error = error_init("Permission denied", (*ast)->cmd[0]);
		return ((*ast)->cmd = NULL, g_error_code = 1, 1);
	}
	else
	{
		(*ast)->error = error_init("command not found", (*ast)->cmd[0]);
		return ((*ast)->cmd = NULL, g_error_code = 127, 127);
	}
	return (0);
}

int	cmd_path_init(t_ast **ast, int i)
{
	char	**path;
	char	*cmd;
	char	*test_path;

	if ((*ast)->cmd == NULL || is_builtin(*ast))
		return (0);
	path = extract_path();
	if (!path)
	{
		(*ast)->error = error_init("No such file or directory", (*ast)->cmd[0]);
		return ((*ast)->cmd = NULL, g_error_code = 127, 127);
	}
	cmd = ft_strjoin("/", (*ast)->cmd[0]);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
		{
			(*ast)->cmd_path = test_path;
			g_error_code = 0;
			return (g_error_code = 0, 0);
		}
	}
	return (check_if_directory(ast));
}

void	add_node_hd(t_heredoc **hd, char *s)
{
	t_heredoc	*new_node;
	t_heredoc	*last_node;

	new_node = mem_manager(sizeof(t_heredoc), 0, 0, 'A');
	new_node->s = ft_strdup(s);
	new_node->next = NULL;
	if (!*hd)
		*hd = new_node;
	else
	{
		last_node = *hd;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

int	add_to_ast(t_ast **ast, t_heredoc *hd, int n)
{
	char	*path;
	int		fd;

	path = ft_strjoin(ft_strdup("/home/adesille/Desktop/minishell/minishell/srcs/parsing/hd"), ft_itoa(n));
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		return (error(strerror(errno), path, 1));
	mem_manager(sizeof(int), 0, fd, 'O');
	while (hd)
	{
		ft_putstr_fd(hd->s, fd);
		if (hd->next)
			ft_putstr_fd("\n", fd);
		hd = hd->next;
	}
	(*ast)->heredoc = 1;
	if ((*ast)->fd_in)
		mem_manager(0, 0, (*ast)->fd_in, 'N');
	(*ast)->fd_in = open(path, O_RDONLY, 0644);
	if ((*ast)->fd_in == -1)
		return (error(strerror(errno), path, 1));
	mem_manager(sizeof(int), 0, (*ast)->fd_in, 'O');
	return (0);
}

int	parse_heredoc(t_ast **ast, char **tokens, int *i, int n)
{
	char		*s;
	char		*del;
	t_heredoc	*hd;
	char		*ss;

	n++;
	printf("HEREDOC\n");
	hd = NULL;
	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		del = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		del = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	while (1)
	{
		s = readline("> ");
		ss = ft_strdup(s);
		free(s);
		if (!ft_strcmp(ss, del))
			break ;
		add_node_hd(&hd, ss);
	}
	get_dollar_hd(hd);
	add_to_ast(ast, hd, n);
	*i += 2;
	return (0);
}
