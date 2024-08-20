/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:55:43 by isb3              #+#    #+#             */
/*   Updated: 2024/08/20 08:55:48 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_utils_quotes(t_split *index, char *s, char **array)
{
	index->k = index->i;
	index->token = s[index->i++];
	while (s[index->i] && s[index->i] != index->token)
		index->i += 1;
	index->i += 1;
	if (s[index->i] && !is_del(s[index->i]))
		index->token = 1;
	else
	{
		array[index->j++] = ft_substr(s, index->k, index->i - index->k);
	}
	return (0);
}

int	split_utils_char(t_split *index, char *s, char **array)
{
	if (index->token == 1)
		index->token = 0;
	else
		index->k = index->i;
	while (s[index->i] && !is_del(s[index->i]) && s[index->i] != '\n')
	{
		if (s[index->i] == 34 || s[index->i] == 39)
			index->i = is_quotes(s, index->i, '?');
		index->i++;
	}
	array[index->j++] = ft_substr(s, index->k, index->i - index->k);
	if (s[index->i] == '\n')
	{
		array[index->j++] = ft_substr("\n", 0, 2);
		index->i++;
	}
	return (0);
}

void	init_i(t_split **index)
{
	(*index)->i = 0;
	(*index)->j = 0;
	(*index)->k = 0;
	(*index)->token = 0;
}

char	**splitter(char **array, char *s)
{
	t_split	*index;

	index = malloc(sizeof(t_split));
	if (!index)
		return (NULL);
	init_i(&index);
	while (s[index->i])
	{
		while (is_del(s[index->i]))
			index->i++;
		if (s[index->i] == 34 || s[index->i] == 39)
		{
			if (split_utils_quotes(index, s, array))
				return (free(index), NULL);
			if (index->token == 1)
				if (split_utils_char(index, s, array))
					return (free(index), NULL);
		}
		else if (s[index->i])
			if (split_utils_char(index, s, array))
				return (free(index), NULL);
	}
	return (array[index->j] = NULL, free(index), array);
}
