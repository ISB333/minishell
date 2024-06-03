/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:06:52 by adesille          #+#    #+#             */
/*   Updated: 2024/06/03 09:45:31 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mem(char **array, size_t j)
{
	while (j-- > 0)
		free(array[j]);
	free(array);
}

size_t	count_rows(char *s)
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
		if (is_sh_ope(s, i, 0) == 2)
			i += 2;
		if (s[i] == 34 || s[i] == 39)
			i = closing_quotes_pos(s, i);
		else
			while (s[i] && !is_del(s[i]))
				i++;
	}
	return (rows);
}

char	**splitter(char **array, char *s, size_t i)
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
			if (s[i] == 34 || s[i] == 39)
				i = closing_quotes_pos(s, i);
			else
				while (s[i] && !is_del(s[i]))
					i++;
			array[j] = ft_substr(s, k, i - k);
			if (!array[j++])
				return (free_mem(array, j - 1), NULL);
		}
	}
	return (array[j] = NULL, array);
}

int	strlen_space(char *s)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (s[len])
		len++;
	while (s[++i])
	{
		if (is_sh_ope(s, i, 0))
			len += 2;
		if (is_sh_ope(s, i, 0) == 2)
			i++;
	}
	if (is_quotes(s, 0, '?') == 34 || is_quotes(s, 0, '?') == 39)
		len++;
	return (len + 1);
}

int	add_space(char **s, int i, int k)
{
	char	*str;

	str = malloc(strlen_space(*s));
	if (!str)
		return (1);
	while ((*s)[i])
	{
		if (is_sh_ope(*s, i, 0))
		{
			str[k++] = ' ';
			str[k++] = (*s)[i++];
			if (is_sh_ope(*s, i - 1, 0) == 2)
				str[k++] = (*s)[i++];
			str[k++] = ' ';
		}
		else
			str[k++] = (*s)[i++];
	}
	if (is_quotes(*s, 0, '?') == 34 || is_quotes(*s, 0, '?') == 39)
		str[k++] = is_quotes(*s, 0, '?');
	str[k] = '\0';
	return (free(*s), *s = str, 0);
}
