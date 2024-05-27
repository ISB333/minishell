/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:51 by adesille          #+#    #+#             */
/*   Updated: 2024/05/27 13:28:27 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_del(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static void	freemem(char **array, size_t j)
{
	while (j-- > 0)
		free(array[j]);
	free(array);
}

static size_t	count_rows(const char *s)
{
	size_t	i;
	size_t	rows;

	rows = 0;
	i = 0;
	while (s[i])
	{
		while (is_del(s[i]))
			i++;
		if (s[i])
			rows++;
		while (s[i] && !is_del(s[i]))
			i++;
	}
	return (rows);
}

static char	**splitter(char **array, const char *s, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (s[i])
	{
		while (is_del(s[i]))
			i++;
		if (s[i])
		{
			k = i;
			while (s[i] && !is_del(s[i]))
				i++;
			array[j] = ft_substr(s, k, i - k);
			if (!array[j])
			{
				freemem(array, j);
				return (NULL);
			}
			j++;
		}
	}
	array[j] = NULL;
	return (array);
}

char	**tokenizer(char const *s)
{
	char	**array;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	array = (char **)malloc((count_rows(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = splitter(array, s, i);
	return (array);
}