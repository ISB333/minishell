/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:35:27 by adesille          #+#    #+#             */
/*   Updated: 2024/06/18 09:14:28 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	while (i-- > 0)
		free(arr[i]);
	free(arr);
}

void	free_fds(t_ast *current)
{
	int	i;

	if (current->fd_in)
	{
		i = -1;
		while (current->fd_in[++i])
			close(current->fd_in[i]);
	}
	if (current->fd_out)
	{
		i = -1;
		while (current->fd_out[++i])
			close(current->fd_out[i]);
	}
	if (current->fd_append)
	{
		i = -1;
		while (current->fd_append[++i])
			close(current->fd_append[i]);
	}
	free(current->fd_in);
	free(current->fd_out);
	free(current->fd_append);
}

void	free_lst(t_ast **ast)
{
	t_ast	*current;
	t_ast	*next;

	current = *ast;
	while (current)
	{
		// if (current->cmd)
		// {
		// 	if (current->cmd_path)
		// 		free(current->cmd_path);
		// }
		// if (current->heredoc)
		// 	free(current->heredoc);
		// free_fds(current);
		next = current->next;
		free(current);
		current = next;
	}
}

int	parse_append(t_ast **ast, char **tokens)
{
	char	*fd;
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (tokens[++i])
	{
		if (is_append(tokens[i], 0, 0))
		{
			if (is_there_quotes_in_da_shit(tokens[i + 1]))
				fd = quotes_destroyer(tokens[i + 1], 0, 0, 0);
			else
				fd = ft_substr(tokens[i + 1], 0, ft_strlen(tokens[i + 1]));
			printf("fd_append = %s\n", fd);
			(*ast)->fd_append[++k] = open(fd, O_WRONLY | O_APPEND, 0644);
			if (!(*ast)->fd_append)
				return (1);
			i += 2;
			free(fd);
		}
		else
			i++;
	}
	return (0);
}
