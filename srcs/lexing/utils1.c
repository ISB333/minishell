/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:06:52 by adesille          #+#    #+#             */
/*   Updated: 2024/05/29 15:36:08 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freemem(char **array, size_t j)
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
		if (is_sh_ope(s, i))
			rows++;
		else if (s[i] && (is_sh_ope(s, i) != 1 || is_sh_ope(s, i) != 2))
			rows++;
		if (is_sh_ope(s, i) == 2)
			i += 2;
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
			while (s[i] && !is_del(s[i]))
				i++;
			array[j] = ft_substr(s, k, i - k);
			if (!array[j])
				return (freemem(array, j), NULL);
			j++;
		}
	}
	return (array[j] = NULL, array);
}

int		strlen_space(char *s)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (s[len])
		len++;
	while (s[++i])
	{
		if (is_sh_ope(s, i))
			len += 2;
		if (is_sh_ope(s, i) == 2)
			i++;
	}
	return (len + 1);
}

char	*add_space(char *s, int i, int k)
{
	char	*str;

	str = malloc(strlen_space(s));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (is_sh_ope(s, i) == 2)
		{
			str[k++] = ' ';
			str[k++] = s[i++];
			str[k++] = s[i++];
			str[k++] = ' ';
		}
		else if (is_sh_ope(s, i))
		{
			str[k++] = ' ';
			str[k++] = s[i++];
			str[k++] = ' ';
		}
		else
			str[k++] = s[i++];
	}
	return (str[k] = '\0', str);
}
