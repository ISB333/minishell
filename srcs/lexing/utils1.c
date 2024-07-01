/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:06:52 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 07:29:17 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_i(t_split **i)
{
	(*i)->i = 0;
	(*i)->j = 0;
	(*i)->k = 0;
	(*i)->token = 0;
}

char	**splitter(char **array, char *s)
{
	t_split	*i;

	i = malloc(sizeof(t_split));
	if (!i)
		return (NULL);
	init_i(&i);
	while (s[i->i])
	{
		while (is_del(s[i->i]))
			i->i++;
		if (s[i->i] == 34 || s[i->i] == 39)
		{
			if (split_utils_quotes(i, s, array))
				return (free(i), NULL);
			if (i->token == 1)
				if (split_utils_char(i, s, array))
					return (free(i), NULL);
		}
		else if (s[i->i])
			if (split_utils_char(i, s, array))
				return (free(i), NULL);
	}
	return (array[i->j] = NULL, free(i), array);
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

void	add_space_utils(char **s, char *str, int *i, int *k)
{
	str[(*k)++] = ' ';
	str[(*k)++] = (*s)[(*i)++];
	if (is_sh_ope(*s, *i - 1, 0) == 2)
		str[(*k)++] = (*s)[(*i)++];
	str[(*k)++] = ' ';
}

int	add_space(char **s, int i, int k, int token)
{
	char	*str;

	str = mem_manager(strlen_space(*s), 0, 0, 'A');
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
			add_space_utils(s, str, &i, &k);
		else
			str[k++] = (*s)[i++];
	}
	return (str[k] = '\0', *s = str, 0);
}
