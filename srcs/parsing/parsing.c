/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:03:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/11 11:05:41 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1. allocate cmd with args
	2. find cmd_path
	3. if is_redirection, open file, else stdin/stdout
*/

void	free_memory(char **array)
{
	int	j;

	j = 0;
	if (!array)
		return ;
	while (array[j])
		j++;
	while (j-- > 0)
		free(array[j]);
	free(array);
}

void	free_lst(t_ast **ast)
{
	t_ast	*current;
	t_ast	*next;

	current = *ast;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int parser(t_ast **ast, char **tokens)
{
	int	i;

	if (!tokens)
		return (printf("lexing error\n"), 1);
	// *ast = malloc(sizeof(t_ast));
	// if (!*ast)
	// 	return (0);
	// i = -1;
	// while (tokens[++i])
	// {
	// 	if (is_redir(tokens[i], 0, '?'))
	// 		parse_redir(ast, tokens, i);
	// 	else if (is_pipe(tokens[i], 0, '?'))
	// 		parse_pipe(ast, tokens, i);
	// 	else if (is_heredoc(tokens[i], 0, '?'))
	// 		parse_heredoc(ast, tokens, i);
	// 	else if (is_append(tokens[i], 0, '?'))
	// 		parse_pipe(ast, tokens, i);
	// 	else
	// 		parse_cmd(ast, tokens, i);
	// }
	// printf("\n");
	// i = -1;
	free_memory(tokens);
	// free_lst(ast);
	return (0);
}
