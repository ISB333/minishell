/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/18 09:32:39 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	len = len_to_pipe(tokens, *i);
	// printf("len = %d\n", len);
	array[*k] = malloc((len + 1) * sizeof(char *));
	if (!array[*k])
		return (1);
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
	printf("len = %d\n", len);
	array = malloc((len + 2) * sizeof(char **));
	if (!array)
		return (NULL);
	array[len + 1] = NULL;
	while (tokens[i])
	{
		if (split_array_utils(array, tokens, &i, &k))
			return (printf("split_array error\n"), NULL);
		if (!tokens[++i])
			return (array);
	}
	return (printf("looooooooooooooooooooool\n"), NULL);
}

int	lexer_utils(char ***array, char **tokens)
{
	int	len;
	int	i;

	len = array_len(tokens);
	array = malloc(2 * sizeof(char **));
	if (!array)
		return (1);
	array[0] = malloc((len + 1) * sizeof(char *));
	if (!array[0])
		return (free(array), 1);
	array[0][len] = NULL;
	i = -1;
	while (tokens[++i])
		array[0][i] = ft_substr(tokens[i], 0, ft_strlen(tokens[i]));
	array[1] = NULL;
	return (0);
}

char	***lexer(char *s)
{
	char	**tokens;
	char	***array;
	size_t	i;

	array = NULL;
	if (!s)
		return (NULL);
	if (is_sh_ope(s, 0, '?'))
		if (add_space(&s, 0, 0, 0))
			return (free(s), NULL);
	if (open_quotes(s))
		return (free(s), printf("Brother, \
			I will smash ur face. Close me dat quote!\n"), NULL);
	tokens = (char **)malloc((count_rows(s, 0) + 1) * sizeof(char *));
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
	else if (lexer_utils(array, tokens))
		return (NULL);
	return (free(s), free_memory(tokens), array);
}
