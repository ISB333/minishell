/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:59:36 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 09:47:28 by isb3             ###   ########.fr       */
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

int	split_utils_quotes(t_split *i, char *s, char **array)
{
	i->k = i->i;
	i->token = s[i->i++];
	while (s[i->i] && s[i->i] != i->token)
		i->i += 1;
	i->i += 1;
	if (s[i->i] && !is_del(s[i->i]))
		i->token = 1;
	else
	{
		array[i->j++] = ft_substr(s, i->k, i->i - i->k);
	}
	return (0);
}

int	split_utils_char(t_split *i, char *s, char **array)
{
	if (i->token == 1)
		i->token = 0;
	else
		i->k = i->i;
	while (s[i->i] && !is_del(s[i->i]) && s[i->i] != '\n')
	{
		if (s[i->i] == 34 || s[i->i] == 39)
			i->i = is_quotes(s, i->i, '?');
		i->i++;
	}
	array[i->j++] = ft_substr(s, i->k, i->i - i->k);
	if (s[i->i] == '\n')
	{
		array[i->j++] = ft_substr("\n", 0, 2);
		i->i++;
	}
	return (0);
}
