/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:37 by adesille          #+#    #+#             */
/*   Updated: 2024/06/27 14:00:39 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redir_utils2(t_ast **ast, char **tokens, int *i)
{
	char	*fd;

	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		fd = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		fd = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	(*ast)->fd_out = open(fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*ast)->fd_out == -1)
		return (printf("minihell: error while opening: %s\n", fd), 1);
	mem_manager(sizeof(int), (*ast)->fd_out, 'O');
	*i += 2;
	return (0);
}

int	parse_redir_utils1(t_ast **ast, char **tokens, int *i)
{
	char	*fd;

	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		fd = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		fd = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	(*ast)->fd_in = open(fd, O_RDONLY);
	if ((*ast)->fd_in == -1)
	{
		init_lst(ast);
		(*ast)->error = ft_strjoin(ft_strjoin("minihell: ", ft_strdup(fd)),
				": No such file or directory");
		return (printf("minihell: %s: No such file or directory\n", fd), 1);
	}
	mem_manager(sizeof(int), (*ast)->fd_in, 'O');
	*i += 2;
	return (0);
}

int	parse_redir(t_ast **ast, char **tokens, int i)
{
	while (tokens[i])
	{
		if (is_redir(tokens[i], 0, 0) == 1)
		{
			if (parse_redir_utils1(ast, tokens, &i))
				return (1);
		}
		else if (is_redir(tokens[i], 0, 0) == 2)
		{
			if (parse_redir_utils2(ast, tokens, &i))
				return (1);
		}
		else if (is_append(tokens[i], 0, 0))
			parse_append(ast, tokens, &i);
		else if (is_heredoc(tokens[i], 0, 0))
			parse_heredoc(ast, tokens, &i);
		else
			i++;
	}
	return (0);
}

int	parse_cmd(t_ast **ast, char **tokens, int *i, int j)
{
	int	k;

	k = *i;
	(*ast)->cmd = mem_manager((strlen_cmd(tokens, i) + 1) * sizeof(char *), 0,
			'A');
	if (!(*ast)->cmd)
		return (1);
	while (tokens[k] && !is_pipe(tokens[k], 0, 0) && !is_new_line(tokens, k))
	{
		if (is_redir(tokens[k], 0, 0))
			k += 2;
		if (is_append(tokens[k], 0, 0))
			k += 2;
		else if (is_there_quotes_in_da_shit(tokens[k]) && tokens[k])
			(*ast)->cmd[++j] = quotes_destroyer(tokens[k++], 0, 0, 0);
		else if (!is_pipe(tokens[k], 0, 0) && !is_new_line(tokens, k))
		{
			(*ast)->cmd[++j] = ft_substr(tokens[k], 0, ft_strlen(tokens[k]));
			k++;
		}
		if (!(*ast)->cmd[j])
			return (1);
	}
	return ((*ast)->cmd[++j] = NULL, 0);
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
