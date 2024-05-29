/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:51 by adesille          #+#    #+#             */
/*   Updated: 2024/05/29 15:40:35 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	-- IGNORE:
	- ''
	- ""
	- not interpret ' or "" or or \ or ;
	- {} or ()
*/

/*
	-- TODO:
	1- Put allocated memory in a struct
	2- Create a switch function
*/

int	is_bad_char(char c)
{
	if (c == 46 || c == 34)
		return (1);
	// if (c == "'")
	// 	return (1);
	// if (c == "'")
	// 	return (1);
	return (0);
}

char	*ignore_bad_char(char *s)
{
	char	*str;
	int		i;
	int		bad;

	i = -1;
	bad = 0;
	while (s[++i])
		if (is_bad_char(s[i]))
			bad++;
	str = malloc(i - bad + 1);
	if (!s)
		return (NULL);
	str[i - bad] = '\0';
	i = 0;
	bad = 0;
	while (s[i])
	{
		if (is_bad_char(s[i]))
			i++;
		str[bad++] = s[i++];
	}
	return (free(s), str);
}

char	**tokenizer(char *s)
{
	char **array;
	char *str = NULL;
	size_t i;

	i = 0;
	if (!s)
		return (NULL);
	str = add_space(s, 0, 0);
	if (!str)
		return (NULL);
	str = ignore_bad_char(str);
	if (!str)
		return (NULL);
	array = (char **)malloc((count_rows(str) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = splitter(array, str, i);
	return (free(str), array);
}
