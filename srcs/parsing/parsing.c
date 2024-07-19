/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:03:35 by adesille          #+#    #+#             */
/*   Updated: 2024/07/19 06:27:47 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi_ll(const char *nptr)
{
	int			i;
	int			sign;
	long long	nbr;

	sign = 1;
	i = 0;
	nbr = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = (nbr * 10) + ((nptr[i++]) - 48);
	return (nbr * sign);
}

void	exit_check(t_ast *ast)
{
	long long	code;

	if (!ast)
		return ;
	if (!ast->next)
	{
		if (ast->cmd && !ft_strcmp(ast->cmd[0], "exit"))
		{
			if (ast->cmd[1])
			{
				code = ft_atoi_ll(ast->cmd[1]);
				if (format_check(ast->cmd[1], &code))
					return (mem_manager(0, 0, 0, 'C'), exit(2));
				if (!ast->cmd[2])
					return (mem_manager(0, 0, 0, 'C'), exit(code));
				else
					error("too many arguments", "exit", 1);
			}
			else
				return (mem_manager(0, 0, 0, 'C'), exit(return_(0, GET)));
		}
	}
	else
		exit_check_utils(ast);
}

int	lst_parse(t_ast **ast, char **tokens, int i, int n)
{
	if (is_redir_in_arr(tokens))
		if (parse_redir(ast, tokens, 0, n))
			return (1);
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

	new_node = mem_manager(sizeof(t_ast), 0, 0, 'A');
	new_node->next = NULL;
	init_lst(&new_node);
	if (!*ast)
		*ast = new_node;
	else
	{
		last_node = return_tail(*ast);
		last_node->next = new_node;
	}
	lst_parse(&new_node, tokens, 0, n);
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
			error("minihell: syntax error near unexpected token 'newline'",
				0, 2);
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
	i = -1;
	while (1)
	{
		tokens = lexer(s);
		if (syntax_checker(tokens, -1))
			return (0);
		if (is_pipe_in_arr(tokens))
			array = split_array(array, tokens, 0, 0);
		else
			lexer_utils(&array, tokens);
		while (array[++i])
			if (add_node(ast, array[i]))
				return (1);
		if (is_open_pipe_in_arr(tokens))
			s = open_pipe_manager();
		else
			break ;
	}
	return (0);
}
