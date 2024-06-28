/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/28 12:23:31 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_to_del(char **tokens, int i)
{
	int	k;

	k = 0;
	if (!tokens[i])
		return (0);
	while (tokens[i] && tokens[i][0] != '|' && tokens[i][0] != '\n')
	{
		i++;
		k++;
	}
	if (tokens[i] && (tokens[i][0] == '|' || tokens[i][0] == '\n'))
		k++;
	return (k);
}

int	split_array_utils(char ***array, char **tokens, int *i, int *k)
{
	int	len;
	int	j;

	len = len_to_del(tokens, *i);
	array[*k] = mem_manager((len + 1) * sizeof(char *), 0, 'A');
	array[*k][len] = NULL;
	j = 0;
	while (tokens[*i] && tokens[*i][0] != '|' && !is_new_line(tokens, *i))
	{
		array[*k][j] = ft_substr(tokens[*i], 0, ft_strlen(tokens[*i]));
		j++;
		(*i)++;
	}
	if (tokens[*i])
	{
		array[*k][j] = ft_substr(tokens[*i], 0, ft_strlen(tokens[*i]));
	}
	(*k)++;
	return (0);
}

char	**arrjoin(char **arr1, char **arr2)
{
	char	**new_arr;
	int		len;
	int		i;
	int		k;

	len = array_len(arr1) + array_len(arr2);
	new_arr = mem_manager((len + 1), 0, 'A');
	new_arr[len] = NULL;
	i = 0;
	k = 0;
	while (arr1[i])
	{
		new_arr[i] = arr1[i];
		i++;
	}
	while (arr2[k])
		new_arr[i++] = arr2[k++];
	return (new_arr);
}

void	add_node_op(t_open_pipe **op, char *str)
{
	t_open_pipe	*new_node;
	t_open_pipe	*last_node;
	int		len;

	len = count_rows(str, 0);
	new_node = mem_manager(sizeof(t_open_pipe), 0, 'A');
	new_node->arr = mem_manager((len + 1) * sizeof(char *), 0, 'A');
	new_node->arr[len] = NULL;
	new_node->arr = splitter(new_node->arr, str);
	new_node->next = NULL;
	if (!*op)
		*op = new_node;
	else
	{
		last_node = *op;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

char **add_to_tokens(t_open_pipe *op, char **tokens)
{
	int			len;
	int			i;
	t_open_pipe	*op_len;
	char		**new_tokens;

	len = 0;
	op_len = op;
	while (op_len)
	{
		i = 0;
		while(op->arr[i])
		{
			i++;
			len++;
		}
		op_len = op_len->next;
	}
	new_tokens = mem_manager((array_len(tokens) + len + 1) * sizeof(char *), 0, 'A');
	new_tokens[len + array_len(tokens)] = NULL;
	len = 0;
	i = 0;
	while (tokens[i])
	{
		new_tokens[i] = tokens[i];
		i++;
	}
	i = 0;
	while (op)
	{
		i = 0;
		while(op->arr[i])
			new_tokens[len++] = ft_strdup(op->arr[i++]);
		op = op->next;
	}
	return(new_tokens);
}

char	**open_pipe_manager(char **tokens)
{
	t_open_pipe *op;
	char	*s;
	char	*str;

	op = NULL;
	while (1)	
	{
		s = readline("> ");
		str = ft_strdup(s);
		free(s);
		if (s)
		{
			add_node_op(&op, str);
		}
		if (!is_open_pipe_in_arr(op->arr))
			break ;
	}
	return (add_to_tokens(op, tokens));
}

char	***split_array(char ***array, char **old_tokens, int i, int k)
{
	int	len;
	char **tokens;

	if (is_open_pipe_in_arr(old_tokens))
	{
		tokens = open_pipe_manager(old_tokens);
	}
	else
		tokens = old_tokens;
	len = is_pipe_in_arr(tokens) + is_new_line_in_arr(tokens);
	array = mem_manager((len + 2) * sizeof(char **), 0, 'A');
	array[len + 1] = NULL;
	while (tokens[i])
	{
		if (split_array_utils(array, tokens, &i, &k))
			return (printf("split_array error\n"), NULL);
		if (!tokens[i])
			return (array);
		else if (tokens[i][0] == '|' || tokens[i][0] == '\n')
			i++;
	}
	return (NULL);
}

int	lexer_utils(char ****array, char **tokens)
{
	int	len;
	int	i;

	len = array_len(tokens);
	*array = mem_manager(2 * sizeof(char **), 0, 'A');
	(*array)[0] = mem_manager((len + 1) * sizeof(char *), 0, 'A');
	(*array)[0][len] = NULL;
	i = -1;
	while (tokens[++i])
		(*array)[0][i] = ft_substr(tokens[i], 0, ft_strlen(tokens[i]));
	(*array)[1] = NULL;
	return (0);
}

char	***lexer(char *s)
{
	char	**tokens;
	char	***array;
	int		len;

	array = NULL;
	if (!s || !ft_strlen(s))
		return (NULL);
	if (is_sh_ope(s, 0, '?'))
		if (add_space(&s, 0, 0, 0))
			return (NULL);
	if (open_quotes(s))
		return (printf("Brother, I will smash ur face. Close me dat quote!\n"),
			NULL);
	len = count_rows(s, 0);
	tokens = mem_manager((len + 1) * sizeof(char *), 0, 'A');
	tokens[len] = NULL;
	tokens = splitter(tokens, s);
	if (is_dollar(tokens, 0, '?', 0))
		get_dollar(tokens);
	if (is_pipe_in_arr(tokens) || is_new_line_in_arr(tokens))
		array = split_array(array, tokens, 0, 0);
	else if (lexer_utils(&array, tokens))
		return (NULL);
	return (array);
}
