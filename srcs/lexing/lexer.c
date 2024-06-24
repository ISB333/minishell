/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/24 08:58:45 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_of_array(char ***arr, int len)
{
	while (--len > 0)
		free_memory(arr[len]);
	free(arr);
}

int	len_to_pipe(char **tokens, int i)
{
	int	k;

	k = 0;
	if (!tokens[i])
		return (0);
	while (tokens[i] && tokens[i][0] != '|')
	{
		i++;
		k++;
	}
	if (tokens[i] && tokens[i][0] == '|')
		k++;
	return (k);
}

int	split_array_utils(char ***array, char **tokens, int *i, int *k)
{
	int	len;
	int	j;
	static int x = 0;

	len = len_to_pipe(tokens, *i);
	printf("len_split_array_utils = %d\n", len);
	array[*k] = malloc((len + 1) * sizeof(char *));
	if (!array[*k])
		return (free(array), 1);
	array[*k][len] = NULL;
	j = 0;
	while (tokens[*i] && tokens[*i][0] != '|')
	{
		array[*k][j] = ft_substr(tokens[*i], 0, ft_strlen(tokens[*i]));
		if (!array[*k][j])
			return (1);
		j++;
		(*i)++;
	}
	if (tokens[*i])
	{
		if (++x == 1)
			array[*k][j]= NULL;
		else
			array[*k][j] = ft_substr(tokens[*i], 0, ft_strlen(tokens[*i]));
		if (!array[*k][j])
			return (1);
	}
	(*k)++;
	return (0);
}

char	***split_array(char ***array, char **tokens, int i, int k)
{
	int	len;

	len = is_pipe_in_arr(tokens);
	printf("len_split_array = %d\n", len);
	array = malloc((len + 2) * sizeof(char **));
	if (!array)
		return (NULL);
	array[len + 1] = NULL;
	while (tokens[i])
	{
		if (split_array_utils(array, tokens, &i, &k))
			return (printf("split_array error\n"), free_array_of_array(array, k), NULL);
		if (!tokens[i])
			return (array);
		else if (tokens[i][0] == '|')
			i++;
	}
	return (printf("looooooooooooooooooooool\n"), NULL);
}

int	lexer_utils(char ****array, char **tokens)
{
	int	len;
	int	i;

	len = array_len(tokens);
	*array = malloc(2 * sizeof(char **));
	if (!*array)
		return (1);
	(*array)[0] = malloc((len + 1) * sizeof(char *));
	if (!(*array)[0])
		return (free(array), 1);
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
	size_t	i;
	int len;

	array = NULL;
	if (!s)
		return (NULL);
	if (is_sh_ope(s, 0, '?'))
		if (add_space(&s, 0, 0, 0))
			return (free(s), NULL);
	if (open_quotes(s))
		return (free(s), printf("Brother, \
			I will smash ur face. Close me dat quote!\n"), NULL);
	len = count_rows(s, 0);
	tokens = malloc((len + 1) * sizeof(char *));
	if (!tokens)
		return (free(s), NULL);
	tokens[len] = NULL;
	tokens = splitter(tokens, s);
	if (!tokens)
		return (free(s), NULL);
	if (is_dollar(tokens, 0, '?', 0))
		if (get_dollar(tokens))
			return (free(s), free_memory(tokens), NULL);
	i = -1;
	while (tokens[++i])
		printf("%zu = %s\n", i, tokens[i]);
	if (is_pipe_in_arr(tokens))
		array = split_array(array, tokens, 0, 0);
	else if (lexer_utils(&array, tokens))
		return (free(s), free_memory(tokens), NULL);
	return (free(s), free_memory(tokens), array);
}
