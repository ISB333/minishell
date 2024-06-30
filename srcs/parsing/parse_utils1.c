/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:33 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 09:30:58 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_path(void)
{
	char	**path;
	char	*trimm_path;

	trimm_path = getenv("PATH");
	if (!trimm_path)
		return (NULL);
	path = ft_split(trimm_path, ':');
	return (path);
}

int	check_if_directory(t_ast *ast)
{
	char	*dir;

	if (!ast->cmd[1] && !access(ast->cmd[0], R_OK))
	{
		dir = ft_strdup(ast->cmd[0]);
		ast->cmd = mem_manager((3 * sizeof(char *)), 0, 0, 'A');
		ast->cmd[0] = ft_strdup("cd");
		return (ast->cmd[1] = dir, ast->cmd[2] = NULL, error_code = 0, 0);
	}
	else if (!access(ast->cmd[0], R_OK) && ast->cmd[1])
	{
		ast->error = error_init("Too many arguments", "cd");
		return (ast->cmd = NULL, error_code = 1, 1);
	}
	else if (is_path(ast->cmd[0]))
	{
		ast->error = error_init("No such file or directory", ast->cmd[0]);
		return (ast->cmd = NULL, error_code = 127, 127);
	}
	else
	{
		ast->error = error_init("command not found", ast->cmd[0]);
		return (ast->cmd = NULL, error_code = 127, 127);
	}
	return (0);
}

int	cmd_path_init(t_ast *ast, int i)
{
	char	**path;
	char	*cmd;
	char	*test_path;

	if (ast->cmd == NULL || !ft_strcmp(ast->cmd[0], "exit"))
		return (0);
	path = extract_path();
	if (!path)
		return (check_if_directory(ast));
	cmd = ft_strjoin("/", ast->cmd[0]);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
		{
			ast->cmd_path = test_path;
			error_code = 0;
			return (0);
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

void	add_to_ast(t_ast **ast, t_heredoc *hd, int n)
{
	char	*path;
	int		fd;

	path = ft_strjoin(ft_strdup("./srcs/parsing/heredoc/hd"), ft_itoa(n));
	fd = open(path, O_RDWR | O_CREAT
			| O_TRUNC | O_APPEND, 0644);
	if (!fd)
		return (perror("Error opening file"));
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
	if (!(*ast)->fd_in)
		return (perror("Error opening file"));
	mem_manager(sizeof(int), 0, (*ast)->fd_in, 'O');
}

int	parse_heredoc(t_ast **ast, char **tokens, int *i, int n)
{
	char		*s;
	char		*heredoc;
	t_heredoc	*hd;

	printf("HEREDOC\n");
	hd = NULL;
	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		heredoc = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		heredoc = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	printf("DEL = %s\n", heredoc);
	while (1)
	{
		s = readline("> ");
		if (!ft_strcmp(s, heredoc))
		{
			free(s);
			break ;
		}
		add_node_hd(&hd, s);
		free(s);
	}
	add_to_ast(ast, hd, n);
	*i += 2;
	return (0);
}
