/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:03:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/05 13:36:10 by adesille         ###   ########.fr       */
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


int	is_redir(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i][0] == '<')
			return ('<');
		if (tokens[i][0] == '>')
			return ('>');
	}
	return (0);
}

int parser(t_ast **ast, char **tokens)
{
	int	i;

	i = -1;
	*ast = malloc(sizeof(t_ast));
	if (!*ast)
		return (0);
	while (is_redir(tokens) == '<')
	{
		while (tokens[++i][0] != '<')
			;
		(*ast)->fd_in = open(tokens[i + 1], O_RDONLY);
		tokens[i][0] = '\0';
		tokens[i + 1][0] = '\0';
		(*ast)->next = NULL;
	}
	(*ast)->next = NULL;
	printf("\n");
	i = -1;
	while (tokens[++i])
		printf("%s\n", tokens[i]);
	free_memory(tokens);
	free_lst(ast);
	return (0);
}
