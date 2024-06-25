/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:37 by adesille          #+#    #+#             */
/*   Updated: 2024/06/25 11:07:49 by adesille         ###   ########.fr       */
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
	if ((*ast)->fd_out)
		close((*ast)->fd_out);
	printf("fd_out = %s\n", fd);
	(*ast)->fd_out = open(fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*ast)->fd_out == -1)
		return (printf("minihell: error while opening: %s\n", fd), 1);
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
	if ((*ast)->fd_in)
		close((*ast)->fd_in);
	printf("fd_in = %s\n", fd);
	(*ast)->fd_in = open(fd, O_RDONLY);
	if ((*ast)->fd_in == -1)
		return (printf("minihell: %s: No such file or directory\n", fd), 1);
	*i += 2;
	return (0);
}

int	parse_redir(t_ast **ast, char **tokens)
{
	int	i;

	i = 0;
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
		else
			i++;
	}
	return (0);
}

int	parse_cmd(t_ast **ast, char **tokens, int *i)
{
	int	k;
	int	j;

	k = *i;
	(*ast)->cmd = mem_manager((strlen_cmd(tokens, i) + 1) * sizeof(char *), \
			0, 'A');
	if (!(*ast)->cmd)
		return (1);
	j = -1;
	while (tokens[k] && !is_pipe(tokens[k], 0, 0))
	{
		if (is_redir(tokens[k], 0, 0))
			k += 2;
		else if (is_there_quotes_in_da_shit(tokens[k]) && tokens[k])
			(*ast)->cmd[++j] = quotes_destroyer(tokens[k++], 0, 0, 0);
		else if (!is_pipe(tokens[k], 0, 0))
		{
			(*ast)->cmd[++j] = ft_substr(tokens[k], 0, ft_strlen(tokens[k]));
			k++;
		}
		if (!(*ast)->cmd[j])
			return (1);
	}
	(*ast)->cmd[++j] = NULL;
	return (0);
}

int	parse_heredoc(t_ast **ast, char **tokens, int *i)
{
	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		(*ast)->heredoc = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		(*ast)->heredoc = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i
					+ 1]));
	if (!(*ast)->heredoc)
		return (printf("heredoc error"), 1);
	*i += 2;
	return (0);
}
