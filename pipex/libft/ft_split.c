/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:08:46 by adesille          #+#    #+#             */
/*   Updated: 2024/03/31 11:12:13 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	freememory(char **array, size_t j)
{
	while (j-- > 0)
		free(array[j]);
	free(array);
}

static size_t	ft_del_rows(char *s, int c)
{
	size_t	i;
	size_t	rows;

	rows = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == 39)
		{
			rows++;
			i++;
			while (s[i] != 39)
				i++;
		}
		else if (s[i])
			rows++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (rows);
}

static char	**ft_cut(char **array, char *s, char c, size_t i)
{
	size_t	j;
	size_t	k;

	j = -1;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			k = i;
			if (s[i] == 39)
				while (s[i] && s[i + 1] != 39)
					i++;
			while (s[i] && s[i] != c)
				i++;
			if (s[k] == 39)
				array[++j] = ft_substr(s, k + 1, i - k - 2);
			else
				array[++j] = ft_substr(s, k, i - k);
			if (!array[j])
				return (freememory(array, j), NULL);
		}
	}
	return (array[++j] = NULL, array);
}

char	**ft_split(char *s, char c)
{
	char	**array;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	array = (char **)malloc((ft_del_rows(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = ft_cut(array, s, c, i);
	return (array);
}
