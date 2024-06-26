/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/26 11:53:46 by adesille         ###   ########.fr       */
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
	int			len;
	int			j;

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

char	***split_array(char ***array, char **tokens, int i, int k)
{
	int	len;

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
	int i = 0;
	// printf("before split: \n");
	// while(tokens[i])
	// 	printf("%s\n", tokens[i++]);
	if (is_pipe_in_arr(tokens) || is_new_line_in_arr(tokens))
		array = split_array(array, tokens, 0, 0);
	else if (lexer_utils(&array, tokens))
		return (NULL);
	i = 0;
	printf("after split: \n");
	while(tokens[i])
		printf("%s", tokens[i++]);
	return (array);
}
