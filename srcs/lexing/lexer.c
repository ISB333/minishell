/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/15 07:23:00 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_quotes(char *s)
{
	int	i;
	int	token;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			if (!s[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	array_len(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		;
	return (i);
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

char	***split_array(char ***array, char **tokens)
{
	int	i;
	int	k;
	int	j;
	int	len;

	k = 0;
	i = 0;
	len = is_pipe_in_arr(tokens);
	array = malloc((len + 2) * sizeof(char **));
	if (!array)
		return (NULL);
	array[len + 1] = NULL;
	while (tokens[i])
	{
		len = len_to_pipe(tokens, i);
		array[k] = malloc((len + 1) * sizeof(char *));
		if (!array[k])
			return (NULL);
		array[k][len] = NULL;
		j = 0;
		while (tokens[i] && tokens[i][0] != '|')
		{
			array[k][j++] = ft_substr(tokens[i], 0, ft_strlen(tokens[i]));
			i++;
		}
		array[k][j++] = ft_substr(tokens[i], 0, ft_strlen(tokens[i]));
		if (!tokens[++i])
			return (array[++k] = NULL, array);
		k++;
	}
	return (array);
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
		array = split_array(array, tokens);
	else
	{
		array = malloc(2 * sizeof(char **));
		if (!array)
			return (NULL);
		array[0] = malloc((i + 1) * sizeof(char *));
		if (!array[0])
			return (free(array), NULL);
		array[0][i] = NULL;
		i = -1;
		while (tokens[++i])
			array[0][i] = ft_substr(tokens[i], 0, ft_strlen(tokens[i]));
		array[1] = NULL;
	}
	return (free(s), free_memory(tokens), array);
}
