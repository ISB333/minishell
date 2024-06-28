/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:33 by adesille          #+#    #+#             */
/*   Updated: 2024/06/28 10:51:52 by adesille         ###   ########.fr       */
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

int	cmd_path_init(t_ast *ast, int i)
{
	char	**path;
	char	*cmd;
	char	*test_path;

	if (ast->cmd == NULL || !ft_strcmp(ast->cmd[0], "exit"))
		return (0);
	path = extract_path();
	if (!path)
	{
		ast->error = error_init("command not found", ast->cmd[0]);
		return (ast->cmd = NULL, error_code = 127, 127);
	}
	cmd = ft_strjoin("/", ast->cmd[0]);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
		{
			ast->cmd_path = test_path;
			return (0);
		}
	}
	ast->error = error_init("command not found", ast->cmd[0]);
	return (ast->cmd = NULL, error_code = 127, 127);
}

void	add_node_hd(t_heredoc **hd, char *s)
{
	t_heredoc	*new_node;
	t_heredoc	*last_node;

	new_node = mem_manager(sizeof(t_heredoc), 0, 'A');
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

void	add_to_ast(t_ast **ast, t_heredoc *hd)
{
	int			len;
	t_heredoc	*hd_len;

	len = 0;
	hd_len = hd;
	while (hd_len)
	{
		len++;
		hd_len = hd_len->next;
	}
	(*ast)->heredoc = mem_manager((len + 1) * sizeof(char *), 0, 'A');
	(*ast)->heredoc[len] = NULL;
	len = 0;
	while (hd)
	{
		(*ast)->heredoc[len++] = ft_strdup(hd->s);
		hd = hd->next;
	}
}

int	parse_heredoc(t_ast **ast, char **tokens, int *i)
{
	char		*s;
	char		*heredoc;
	t_heredoc	*hd;

	hd = NULL;
	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		heredoc = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		heredoc = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
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
	add_to_ast(ast, hd);
	*i += 2;
	return (0);
}
