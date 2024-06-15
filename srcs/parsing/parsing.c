/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:03:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/15 07:30:04 by isb3             ###   ########.fr       */
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
	========================================================
	TODO 1:	Norme
	TODO 2:	Protect Malloc + Error cases
	TODO 3:	Correct for cases of multi redirection
	TODO 4:	Heredoc 
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
	int		i;

	current = *ast;
	while (current)
	{
		i = -1;
		if (current->cmd)
		{
			while (current->cmd[++i])
				;
			while (i-- > 0)
				free(current->cmd[i]);
			free(current->cmd);
			if (current->cmd_path)
				free(current->cmd_path);
		}
		if (current->heredoc)
			free(current->heredoc);
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
		next = current->next;
		free(current);
		current = next;
	}
}

int	strlen_minus_quotes(char *s, int token, int len)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			i++;
			len += 2;
		}
		if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			i++;
			len += 2;
		}
		else
			i++;
	}
	return (i - len);
}

char	*quotes_destroyer(char *s, int i, int k, int token)
{
	char	*new_s;

	new_s = malloc(strlen_minus_quotes(s, 0, 0) + 1);
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				new_s[k++] = s[i++];
			i++;
		}
		if (s[i] == 39)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				new_s[k++] = s[i++];
			i++;
		}
		else
			new_s[k++] = s[i++];
	}
	return (new_s[k] = '\0', new_s);
}

int	parse_redir(t_ast **ast, char **tokens)
{
	char	*fd;
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
			if (is_there_quotes_in_da_shit(tokens[i + 1]))
				fd = quotes_destroyer(tokens[i + 1], 0, 0, 0);
			else
				fd = ft_substr(tokens[i + 1], 0, ft_strlen(tokens[i + 1]));
			(*ast)->fd_in[++k] = open(fd, O_RDONLY);
			if (!(*ast)->fd_in[k])
				return (1);
			i += 2;
			// printf("fd_redir = %s\n", fd);
			free(fd);
		}
		else if (is_redir(tokens[i], 0, 0) == 2)
		{
			if (is_there_quotes_in_da_shit(tokens[i + 1]))
				fd = quotes_destroyer(tokens[i + 1], 0, 0, 0);
			else
				fd = ft_substr(tokens[i + 1], 0, ft_strlen(tokens[i + 1]));
			(*ast)->fd_out[++j] = open(fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!(*ast)->fd_out[j])
				return (1);
			i += 2;
			// printf("fd_redir = %s\n", fd);
			free(fd);
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
	int	len;

	k = *i;
	len = 0;
	while (tokens[*i] && !is_pipe(tokens[*i], 0, 0))
	{
		if (is_redir(tokens[*i], 0, 0))
			(*i) += 2;
		else
		{
			(*i)++;
			len++;
		}
	}
	(*ast)->cmd = malloc((len + 1) * sizeof(char *));
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

int	lst_parse(t_ast **ast, char **tokens)
{
	int	i;

	// int	p;
	// int token;
	i = 0;
	// p = -1;
	// token = 0;
	// while (!is_pipe(tokens[++p], p, '?') && !is_newline())
	// 	;
	// while (i < p)
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

int	allocate_fds(t_ast **ast, char **tokens, int i, int in_len)
{
	int	out_len;
	int	app_len;

	out_len = 0;
	app_len = 0;
	while (tokens[i] && tokens[i][0] != '|')
	{
		if (is_redir(tokens[i], 0, 0) == 1)
		{
			i++;
			in_len++;
		}
		if (is_redir(tokens[i], 0, 0) == 2)
		{
			i++;
			out_len++;
		}
		if (is_append(tokens[i], 0, 0))
		{
			i += 2;
			app_len++;
		}
		else
			i++;
	}
	(*ast)->fd_in = malloc((in_len + 1) * sizeof(int));
	(*ast)->fd_out = malloc((out_len + 1) * sizeof(int));
	(*ast)->fd_append = malloc((app_len + 1) * sizeof(int));
	if (!(*ast)->fd_in || !(*ast)->fd_out || !(*ast)->fd_append)
		return (1);
	(*ast)->fd_in[in_len] = 0;
	(*ast)->fd_out[out_len] = 0;
	(*ast)->fd_append[app_len] = 0;
	return (0);
}

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

void	init_lst(t_ast **ast)
{
	(*ast)->cmd = NULL;
	(*ast)->cmd_path = NULL;
	(*ast)->heredoc = NULL;
	(*ast)->fd_in = 0;
	(*ast)->fd_out = 0;
	(*ast)->fd_append = 0;
	(*ast)->pipe = 0;
}

t_ast	*return_tail(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast->next)
		ast = ast->next;
	return (ast);
}

char	**extract_path(void)
{
	char	**path;
	char	*trimm_path;

	trimm_path = getenv("PATH");
	if (!trimm_path)
		return (NULL);
	path = ft_split(trimm_path, ':');
	if (!path)
		return (NULL);
	return (path);
}

int	cmd_path_init(t_ast *ast)
{
	char	**path;
	char	*cmd;
	char	*test_path;
	int		i;

	path = extract_path();
	if (!path)
		return (printf("path not existing\n"), 1);
	i = -1;
	cmd = ft_strjoin("/", ast->cmd[0]);
	if (!cmd)
		return (free_memory(path), 1);
	while (path[++i])
	{
		test_path = ft_strjoin(path[i], cmd);
		if (!access(test_path, R_OK))
		{
			ast->cmd_path = test_path;
			return (free(cmd), free_memory(path), 0);
		}
		free(test_path);
	}
	return (free(cmd), free_memory(path), printf("%s: notexisting\n",
			ast->cmd[0]), 1);
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
	if (is_redir_in_arr(tokens))
		if (allocate_fds(&new_node, tokens, 0, 0))
			return (free_memory(tokens), free_lst(ast), 1);
	if (lst_parse(&new_node, tokens))
		return (free_memory(tokens), free_lst(ast), 1);
	if (cmd_path_init(new_node))
		return (free_memory(tokens), free_lst(ast), 1);
	if (!*ast)
		*ast = new_node;
	else
	{
		last_node = return_tail(*ast);
		last_node->next = new_node;
	}
	return (0);
}

int	parser(t_ast **ast, char ***array)
{
	int	i;
	int	k;

	if (!array)
		return (printf("lexing error\n"), 1);
	printf("\n\n");
	i = -1;
	while (array[++i])
		if (add_node(ast, array[i]))
			return (printf("parsing error\n"));
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
	i = -1;
	while (array[++i])
		free_memory(array[i]);
	free(array);
	printf("\033[0;33m");
	printf("\n============= LINKED_LIST =============\n\n");
	printf("\033[0;37m");
	print_lst(*ast);
	printf("\033[0m");
	free_lst(ast);
	return (0);
}
