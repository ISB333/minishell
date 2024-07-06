/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:03:35 by adesille          #+#    #+#             */
/*   Updated: 2024/07/06 06:26:18 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_ast *ast)
{
	int	i;
	int	n;

	n = 1;
	if (!ast)
		return ;
	printf("\033[0;33m");
	printf("\n============= LINKED_LIST =============\n\n");
	printf("\033[0;37m");
	while (ast)
	{
		printf("\033[0;33m");
		printf("\n       ------- LIST n°%d -------\n\n", n);
		printf("\033[0;37m");
		i = -1;
		if (ast->cmd)
		{
			while (ast->cmd[++i])
				printf("%s\n", ast->cmd[i]);
			printf("cmd_path = %s\n", ast->cmd_path);
		}
		printf("fd_in = %d\n", ast->fd_in);
		printf("fd_out = %d\n", ast->fd_out);
		if (ast->append)
			printf("APPEND\n");
		if (ast->pipe)
			printf("PIPE\n");
		if (ast->new_line)
			printf("NEWLINE\n");
		if (ast->error)
			printf("ERROR: %s\n", ast->error);
		ast = ast->next;
		n++;
	}
	if (g_error_code)
		printf("error_code = %d\n", g_error_code);
	printf(DEF);
}

void	printer(char ***array)
{
	int	i;
	int	k;

	i = -1;
	k = -1;
	printf("\033[0;34m");
	printf("\n============= ARRAY =============\n\n");
	printf("\033[0;37m");
	while (array[++i])
	{
		k = -1;
		printf("\033[0;36m");
		printf("\n\narray n°%d:\n", i + 1);
		printf("\033[0;37m");
		while (array[i][++k])
			printf("%s\n", array[i][k]);
	}
	printf("\033[0m\n");
}

void	exit_check_utils(t_ast *ast)
{
	int	code;

	while (ast->next)
		ast = ast->next;
	if (ast->cmd && !ft_strcmp(ast->cmd[0], "exit\0"))
	{
		code = ft_atoi(ast->cmd[1]);
		if (ast->cmd[1])
		{
			if (format_check(ast->cmd[1], &code))
				return (mem_manager(0, 0, 0, 'C'), exit(2));
			return (mem_manager(0, 0, 0, 'C'), exit(code));
		}
		return (mem_manager(0, 0, 0, 'C'), exit(EXIT_SUCCESS));
	}
}

void	exit_check(t_ast *ast)
{
	int	code;

	if (!ast)
		return ;
	if (!ast->next)
	{
		if (ast->cmd && !ft_strcmp(ast->cmd[0], "exit"))
		{
			if (ast->cmd[1])
			{
				code = ft_atoi(ast->cmd[1]);
				if (format_check(ast->cmd[1], &code))
					return (mem_manager(0, 0, 0, 'C'), exit(2));
				if (!ast->cmd[2])
					return (mem_manager(0, 0, 0, 'C'), exit(code));
				else
					error("too many arguments", "exit", 1);
			}
			else
				return (mem_manager(0, 0, 0, 'C'), exit(EXIT_SUCCESS));
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
		{
			(*ast)->pipe = 1;
			i++;
		}
		else if (is_new_line(tokens, i))
		{
			(*ast)->new_line = 1;
			i++;
		}
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
	if (is_pipe(tokens[0], 0, 0))
		return (printf("minihell: syntax error near unexpected token '%s'\n",
				tokens[i + 1]));
	while (tokens[++i])
	{
		if (is_sh_ope(tokens[i], 0, 0) && !is_pipe(tokens[i], 0, 0) && !tokens[i
			+ 1])
		{
			printf("minihell: syntax error near unexpected token 'newline'\n");
			return (1);
		}
		if (is_sh_ope(tokens[i], 0, 0) && is_sh_ope(tokens[i + 1], 0, 0))
		{
			if (!is_pipe(tokens[i], 0, 0) && (!is_redir(tokens[i + 1], 0, 0)
					|| !is_append(tokens[i + 1], 0, 0) || !is_heredoc(tokens[i
						+ 1], 0, 0)))
			{
				printf("minihell: syntax error near unexpected token '%s'\n",
					tokens[i + 1]);
				return (1);
			}
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
		if (is_pipe_in_arr(tokens) || is_new_line_in_arr(tokens))
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
