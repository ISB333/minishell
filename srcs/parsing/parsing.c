/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:03:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/28 12:28:15 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	! / If multiple heredoc no pipes, only the last is took,
	!	else first del then 2nd del etc..
			? ---> Test more cuz da shit is weird

	! If multiple infiles or outfiles only the last infile/outfile is taken,
	! 	but still create the multiple outfile, and send an error message
	!				if file exist (except for append):
	!		- bash: out1: cannot overwrite existing file

	! If open pipe, shell open an heredoc like waiting for a command

	========================================================
	TODO 0: Open pipe
		- Call Lexer from Parser
			-> If open_pipe
				-> while (1)
					- lexer()
					- add_node()
					if(!open_pipe)
						break
				return(new_array);
	TODO 1: List every returns code possible & set them with exit(*return code*)
	TODO 2: If a path is given, try to execute it

	TODO ?: man
*/

void	print_lst(t_ast *ast)
{
	int	i;
	int	n;

	n = 1;
	if (!ast)
		return ;
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
		if (ast->infile)
			printf("INFILE\n");
		if (ast->outfile)
			printf("OUTFILE\n");
		if (ast->append)
			printf("APPEND\n");
		if (ast->pipe)
			printf("PIPE\n");
		if (ast->new_line)
			printf("NEWLINE\n");
		i = -1;
		if (ast->heredoc)
		{
			printf("HEREDOC:\n");
			while (ast->heredoc[++i])
				printf("%s\n", ast->heredoc[i]);
		}
		if (ast->error)
			printf("%s\n", ast->error);
		ast = ast->next;
		n++;
	}
	if (error_code)
		printf("error_code = %d\n", error_code);
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

int	lst_parse(t_ast **ast, char **tokens, int i)
{
	if (is_redir_in_arr(tokens))
		if (parse_redir(ast, tokens, 0))
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
	t_ast	*new_node;
	t_ast	*last_node;

	new_node = mem_manager(sizeof(t_ast), 0, 'A');
	new_node->next = NULL;
	init_lst(&new_node);
	if (!*ast)
		*ast = new_node;
	else
	{
		last_node = return_tail(*ast);
		last_node->next = new_node;
	}
	if (lst_parse(&new_node, tokens, 0))
		return (1);
	cmd_path_init(new_node, -1);
	return (0);
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
			return (mem_manager(0, 0, 'C'), exit(code));
		return (mem_manager(0, 0, 'C'), exit(EXIT_SUCCESS));
	}
}

void	exit_check(t_ast *ast)
{
	int	code;

	if (!ast->next)
	{
		if (ast->cmd && !ft_strcmp(ast->cmd[0], "exit\0"))
		{
			if (ast->cmd[1])
			{
				code = ft_atoi(ast->cmd[1]);
				if (code > 255)
					code -= 256;
				if (!ast->cmd[2])
					return (mem_manager(0, 0, 'C'), exit(code));
				else
					error("too many arguments", "exit", 1);
			}
			else
				return (mem_manager(0, 0, 'C'), exit(EXIT_SUCCESS));
		}
	}
	else
		exit_check_utils(ast);
}

int	parser(t_ast **ast, char ***array)
{
	int	i;

	if (!array)
		return (printf("%slexing error%s\n", RED, DEF), 1);
	printf("\n\n");
	printer(array);
	i = -1;
	while (array[++i])
		if (add_node(ast, array[i]))
			return (1);
	exit_check(*ast);
	printf("\033[0;33m");
	printf("\n============= LINKED_LIST =============\n\n");
	printf("\033[0;37m");
	print_lst(*ast);
	printf("\033[0m");
	return (0);
}
