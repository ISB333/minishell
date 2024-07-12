/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:37 by adesille          #+#    #+#             */
/*   Updated: 2024/07/12 13:04:08 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_append(t_ast **ast, char **tokens, int *i)
{
	char	*fd;

	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		fd = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		fd = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	(*ast)->fd_out = open(fd, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*ast)->fd_out == -1)
	{
		(*ast)->error = error_init(strerror(errno), fd);
		(*ast)->error_code = 1;
		return (g_error_code = 1, 1);
	}
	mem_manager(sizeof(int), 0, (*ast)->fd_out, 'O');
	*i += 2;
	return (0);
}

int	parse_redir_utils2(t_ast **ast, char **tokens, int *i)
{
	char	*fd;

	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		fd = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		fd = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	if ((*ast)->fd_out)
		mem_manager(0, 0, (*ast)->fd_out, 'N');
	(*ast)->fd_out = open(fd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if ((*ast)->fd_out == -1)
	{
		(*ast)->error = error_init(strerror(errno), fd);
		(*ast)->error_code = 1;
		return (g_error_code = 1, 1);
	}
	mem_manager(sizeof(int), 0, (*ast)->fd_out, 'O');
	*i += 2;
	return (0);
}

int	parse_redir_utils1(t_ast **ast, char **tokens, int *i)
{
	char	*fd;

	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		fd = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		fd = ft_strdup(tokens[*i + 1]);
	if ((*ast)->fd_in)
		mem_manager(0, 0, (*ast)->fd_in, 'N');
	(*ast)->fd_in = open(fd, O_RDONLY);
	if ((*ast)->fd_in == -1)
	{
		// init_lst(ast);
		(*ast)->error = error_init(strerror(errno), fd);
		(*ast)->error_code = 1;
		return (g_error_code = 1, 1);
	}
	mem_manager(sizeof(int), 0, (*ast)->fd_in, 'O');
	*i += 2;
	return (0);
}

int	parse_redir(t_ast **ast, char **tokens, int i, int n)
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
		{
			if (parse_append(ast, tokens, &i))
				return (1);
		}
		else if (is_heredoc(tokens[i], 0, 0))
			parse_heredoc(ast, tokens, &i, n);
		else
			i++;
	}
	return (0);
}

int	parse_cmd(t_ast **ast, char **tok, int *i, int j)
{
	int	k;

	k = *i;
	(*ast)->cmd = mem_manager((cmdlen(tok, i) + 1) * sizeof(char *), 0, 0, 'A');
	if (!(*ast)->cmd)
		return (1);
	while (tok[k] && !is_pipe(tok[k], 0, 0) && !is_new_line(tok, k))
	{
		if (is_redir(tok[k], 0, 0))
			k += 2;
		else if (is_append(tok[k], 0, 0))
			k += 2;
		else if (is_heredoc(tok[k], 0, 0))
			k += 2;
		else if (is_there_quotes_in_da_shit(tok[k]) && tok[k])
			(*ast)->cmd[++j] = quotes_destroyer(tok[k++], 0, 0, 0);
		else if (!ft_strlen(tok[k]))
			k++;
		else if (!is_pipe(tok[k], 0, 0) && !is_new_line(tok, k))
		{
			(*ast)->cmd[++j] = ft_substr(tok[k], 0, ft_strlen(tok[k]));
			k++;
		}
		if (!(*ast)->cmd[j])
			return (1);
	}
	return ((*ast)->cmd[++j] = NULL, 0);
}
