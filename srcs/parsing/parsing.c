/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:03:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/18 11:25:25 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1. allocate cmd with args
	2. find cmd_path
	3. if is_redirection, open file, else stdin/stdout

	! / If multiple heredoc no pipes, only the last is took,
	!	else first del then 2nd del etc..
			? ---> Test more cuz da shit is weird

	! If multiple infiles or outfiles only the last infile/outfile is taken,
	! 	but still create the multiple outfile, and send an error message
	!	 		if file exist (except for append):
	!		- bash: out1: cannot overwrite existing file

	! If open pipe, shell open an heredoc like waiting for a command

	========================================================
	TODO 1:	Norme
	TODO 2:	Protect Malloc
		--> <in <"i"n "cmd" arg | << d'e'l cmd arg > o"u"'t' | c"at" >' 'ou't' 'j'| echo "blabla$USER test"
			== parsing_error + leaks
	TODO 3: Error Management
	TODO 4:	Correct for cases of multi redirection
	TODO 5:	Heredoc
*/

void	print_lst(t_ast *ast)
{
	int	i;
	int	n;

	n = 1;
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
		printf("\nheredoc = %s\n", ast->heredoc);
		if (ast->fd_in)
		{
			i = -1;
			while (ast->fd_in[++i])
				;
			printf("\nfd_in len = %d\n", i);
		}
		if (ast->fd_out)
		{
			i = -1;
			while (ast->fd_out[++i])
				;
			printf("fd_out len = %d\n", i);
		}
		if (ast->fd_append)
		{
			i = -1;
			while (ast->fd_append[++i])
				;
			printf("fd_append len = %d\n", i);
		}
		ast = ast->next;
		n++;
	}
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

int	lst_parse(t_ast **ast, char **tokens)
{
	int	i;

	i = 0;
	/*
	p = -1;
	token = 0;
	while (!is_pipe(tokens[++p], p, '?') && !is_newline())
		;
	while (i < p)
	*/
	if (is_redir(tokens[i], 0, '?'))
		if (parse_redir(ast, tokens))
			return (1);
	if (is_append(tokens[i], 0, '?'))
		parse_append(ast, tokens);
	while (tokens[i])
	{
		if (is_redir(tokens[i], 0, 0))
			i += 2;
		else if (is_append(tokens[i], 0, 0))
			i += 2;
		else if (is_heredoc(tokens[i], 0, 0))
			parse_heredoc(ast, tokens, &i);
		else if (is_pipe(tokens[i], 0, 0))
		{
			(*ast)->pipe = 1;
			i++;
		}
		else
			parse_cmd(ast, tokens, &i);
	}
	return (0);
}

int	add_node(t_ast **ast, char **tokens)
{
	t_ast	*new_node;
	t_ast	*last_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (-1);
	new_node->next = NULL;
	init_lst(&new_node);
	if (!*ast)
		*ast = new_node;
	else
	{
		last_node = return_tail(*ast);
		last_node->next = new_node;
	}
	if (is_redir_in_arr(tokens))
		if (allocate_fds(&new_node, tokens))
			return (1);
	if (lst_parse(&new_node, tokens))
		return (1);
	if (cmd_path_init(new_node))
		return (1);
	return (0);
}

int	parser(t_ast **ast, char ***array)
{
	int	i;

	if (!array)
		return (printf("%slexing error%s\n", RED, DEF), 1);
	printf("\n\n");
	i = -1;
	printer(array);
	while (array[++i])
		if (add_node(ast, array[i]))
			printf("%sparsing error%s\n", RED, DEF);
	i = -1;
	while (array[++i])
		free_memory(array[i]);
	free(array);
	printf("\033[0;33m");
	printf("\n============= LINKED_LIST =============\n\n");
	printf("\033[0;37m");
	print_lst(*ast);
	printf("\033[0m");
	// ff('S');
	free_lst(ast);
	return (0);
}
