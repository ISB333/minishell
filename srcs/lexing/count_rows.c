/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_rows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:59:36 by adesille          #+#    #+#             */
/*   Updated: 2024/08/20 06:58:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_utils_quotes(int *token, char *s, int i)
{
	*token = s[i];
	while (s[++i] && s[i] != *token)
		;
	if (s[i])
		i++;
	else if (!is_del(s[i]) && s[i])
		*token = 1;
	return (i);
}

int	count_utils_char(int *rows, int *token, char *s, int i)
{
	if (*token == 1)
		*token = 0;
	else
		*rows += 1;
	while (s[i] && !is_del(s[i]) && s[i] != '\n')
	{
		i++;
		if (s[i] == 34 || s[i] == 39)
			i = is_quotes(s, i, '?');
	}
	if (s[i] == '\n')
	{
		i++;
		*rows += 1;
	}
	return (i);
}

int	count_rows(char *s, int rows)
{
	int	i;
	int	token;

	i = 0;
	token = 0;
	while (s[i])
	{
		while (is_del(s[i]))
			i++;
		if (s[i] == 34 || s[i] == 39)
		{
			rows++;
			while (s[i] == 34 || s[i] == 39)
				i = count_utils_quotes(&token, s, i);
			if (token == 1)
				i = count_utils_char(&rows, &token, s, i);
		}
		else if (s[i])
			i = count_utils_char(&rows, &token, s, i);
	}
	return (rows);
}
