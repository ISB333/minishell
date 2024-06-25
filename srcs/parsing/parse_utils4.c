/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:35:27 by adesille          #+#    #+#             */
/*   Updated: 2024/06/25 07:46:45 by adesille         ###   ########.fr       */
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

void	free_lst(t_ast **ast)
{
	t_ast	*current;
	t_ast	*next;

	if (!ast || !*ast)
		return ;
	current = *ast;
	while (current)
	{
		if (current->fd_in)
			close(current->fd_in);
		if (current->fd_out)
			close(current->fd_out);
		if (current->fd_append)
			close(current->fd_append);
		next = current->next;
		free(current);
		current = next;
	}
	*ast = NULL;
}

int	parse_append(t_ast **ast, char **tokens)
{
	char	*fd;
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (is_append(tokens[i], 0, 0))
		{
			if (is_there_quotes_in_da_shit(tokens[i + 1]))
				fd = quotes_destroyer(tokens[i + 1], 0, 0, 0);
			else
				fd = ft_substr(tokens[i + 1], 0, ft_strlen(tokens[i + 1]));
			printf("fd_append = %s\n", fd);
			if ((*ast)->fd_append)
				close((*ast)->fd_append);
			(*ast)->fd_append = open(fd, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if ((*ast)->fd_append == -1)
				return (printf("%serror while opening: %s%s\n", RED, fd, DEF),
					1);
			i += 2;
		}
		else
			i++;
	}
	return (0);
}
