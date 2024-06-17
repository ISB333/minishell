/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:10:37 by adesille          #+#    #+#             */
/*   Updated: 2024/06/17 11:53:16 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redir_utils2(t_ast **ast, char **tokens, int *j, int *i)
{
	char	*fd;

	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		fd = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		fd = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	(*ast)->fd_out[++(*j)] = open(fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!(*ast)->fd_out[*j])
		return (1);
	*i += 2;
	// printf("fd_redir = %s\n", fd);
	free(fd);
	return (0);
}

int	parse_redir_utils1(t_ast **ast, char **tokens, int *k, int *i)
{
	char	*fd;

	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		fd = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		fd = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	(*ast)->fd_in[++(*k)] = open(fd, O_RDONLY);
	if (!(*ast)->fd_in[*k])
		return (1);
	// printf("fd_redir = %s\n", fd);
	*i += 2;
	free(fd);
	return (0);
}

int	parse_redir(t_ast **ast, char **tokens)
{
	int		k;
	int		j;
	int		i;

	i = 0;
	k = -1;
	j = -1;
	while (tokens[i])
	{
		if (is_redir(tokens[i], 0, 0) == 1)
		{
			if (parse_redir_utils1(ast, tokens, &k, &i))
				return (printf("fd_in error\n"), 1);
		}
		else if (is_redir(tokens[i], 0, 0) == 2)
		{
			if (parse_redir_utils2(ast, tokens, &j, &i))
				return (printf("fd_out error\n"), 1);
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
	(*ast)->cmd = malloc((strlen_cmd(tokens, i) + 1) * sizeof(char *));
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
		// printf("\ncmd = %s\n", (*ast)->cmd[j]);
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
		return (1);
	*i += 2;
	return (0);
}
