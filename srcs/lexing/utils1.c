/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:06:52 by adesille          #+#    #+#             */
/*   Updated: 2024/06/11 10:17:54 by adesille         ###   ########.fr       */
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
	int		token;

	rows = 0;
	i = 0;
	while (s[i])
	{
		while (is_del(s[i]))
			i++;
		if (s[i] == 34 || s[i] == 39)
		{
			token = s[i++];
			rows++;
			while (s[i] && s[i] != token)
				i++;
			i++;
			if (!is_del(s[i]) && s[i])
				token = 1;
		}
		else if (s[i])
		{
			if (token == 1)
				token = 0;
			else
				rows++;
			while (s[++i] && !is_del(s[i]) && s[i] != '\n')
				if (s[i] == 34 || s[i] == 39)
					i = is_quotes(s, i, '?');
			if (s[i] == '\n')
				rows++;
		}
	}
	// printf("%zu\n", rows);
	return (rows);
}

char	**splitter(char **array, char *s)
{
	int	i;
	int	k;
	size_t j = 0;
	int		token;

	i = 0;
	if (!array)
		return (NULL);
	while (s[i])
	{
		while (is_del(s[i]))
			i++;
		if (s[i] == 34 || s[i] == 39)
		{
			k = i;
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			i++;
			if (!is_del(s[i]) && s[i])
				token = 1;
			else
			{
				array[j] = ft_substr(s, k, i - k);
				if (!array[j++])
					return (free_mem(array, j - 1), NULL);
			}
		}
		if (s[i])
		{
			if (token == 1)
				token = 0;
			else
				k = i;
			while (s[++i] && !is_del(s[i]) && s[i] != '\n')
			{
				if (s[i] == 34 || s[i] == 39)
					i = is_quotes(s, i, '?');
			}
			array[j] = ft_substr(s, k, i - k);
			if (!array[j++])
				return (free_mem(array, j - 1), NULL);
			if (s[i] == '\n')
			{
				array[j] = ft_substr("\n", 0, 2);
				if (!array[j++])
					return (free_mem(array, j - 1), NULL);
				i++;
			}
		}
	}
	return (array[j] = NULL, array);
}

int	strlen_space(char *s)
{
	int	len;
	int	i;
	int	token;

	len = 0;
	i = -1;
	while (s[len])
		len++;
	while (s[++i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
		}
		if (is_sh_ope(s, i, 0))
			len += 2;
		if (is_sh_ope(s, i, 0) == 2)
			i++;
	}
	return (len + 1);
}

int	add_space(char **s, int i, int k, int token)
{
	char	*str;

	str = malloc(strlen_space(*s));
	if (!str)
		return (1);
	while ((*s)[i])
	{
		if ((*s)[i] == 34 || (*s)[i] == 39)
		{
			token = (*s)[i];
			str[k++] = (*s)[i++];
			while ((*s)[i] && (*s)[i] != token)
				str[k++] = (*s)[i++];
		}
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
	return (str[k] = '\0', free(*s), *s = str, 0);
}
