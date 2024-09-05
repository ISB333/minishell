/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:03:35 by adesille          #+#    #+#             */
/*   Updated: 2024/09/05 13:34:56 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_parse(t_ast **ast, char **tokens, int i, int n)
{
	if (is_redir_in_arr(tokens))
		if (parse_redir(ast, tokens, 0, n))
			return (-1);
	while (tokens[i])
	{
		if (is_redir(tokens[i], 0, 0))
			i += 2;
		else if (is_append(tokens[i], 0, 0))
			i += 2;
		else if (is_heredoc(tokens[i], 0, 0))
			i += 2;
		else if (is_pipe(tokens[i], 0, 0))
			i++;
		else
			parse_cmd(ast, tokens, &i, -1);
	}
	return (0);
}

int	add_node(t_ast **ast, char **tokens)
{
	static int	n = 0;
	t_ast		*new_node;
	t_ast		*last_node;

	new_node = mem_manager(sizeof(t_ast), 0, 0, ALLOCATE);
	new_node->next = NULL;
	init_lst(&new_node);
	if (!*ast)
		*ast = new_node;
	else
	{
		last_node = return_tail(*ast);
		last_node->next = new_node;
	}
	if (lst_parse(&new_node, tokens, 0, n))
		return (0);
	cmd_path_init(&new_node, -1);
	return (0);
}

int	syntax_checker(char **tokens, int i)
{
	if (!tokens)
		return (1);
	if (is_pipe(tokens[0], 0, 0))
		return (error("minihell: syntax error near unexpected token",
				tokens[i + 1], 2));
	while (tokens[++i])
	{
		if (is_sh_ope(tokens[i], 0, 0) && !is_pipe(tokens[i], 0, 0)
			&& !tokens[i + 1])
		{
			error("minihell: syntax error near unexpected token 'newline'", 0,
				2);
			return (1);
		}
		if (is_sh_ope(tokens[i], 0, 0) && is_sh_ope(tokens[i + 1], 0, 0))
		{
			if ((is_pipe(tokens[i], 0, 0) && is_pipe(tokens[i + 1], 0, 0))
				|| (!is_pipe(tokens[i], 0, 0) && (!is_redir(tokens[i + 1], 0, 0)
						|| !is_append(tokens[i + 1], 0, 0)
						|| !is_heredoc(tokens[i + 1], 0, 0))))
				return (error("minihell: syntax error near unexpected token",
						tokens[i + 1], 2));
		}
	}
	return (0);
}

int	parser(t_ast **ast, char *s)
{
	char	**tokens;
	char	***array;
	int		i;

	if (is_only_del(s))
		return (0);
	while (1)
	{
		i = -1;
		tokens = lexer(s);
		if (syntax_checker(tokens, -1))
			return (0);
		if (is_pipe_in_arr(tokens))
			array = split_array(array, tokens, 0, 0);
		else
			lexer_utils(&array, tokens);
		while (array[++i])
			if (add_node(ast, array[i]))
				return (-1);
		if (is_open_pipe_in_arr(tokens))
		{
			if (!open_pipe_manager(&s))
				return (*ast = NULL, 0);
		}
		else
			break ;
	}
	return (0);
}
