/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:06:52 by adesille          #+#    #+#             */
/*   Updated: 2024/08/29 11:26:07 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_space(char *s)
{
	int	len;
	int	i;
	int	token;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	while (s[i])
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
		else if (s[i])
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

	str = mem_manager(strlen_space(*s), 0, 0, ALLOCATE);
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
		else if ((*s)[i])
			str[k++] = (*s)[i++];
	}
	return (str[k] = '\0', *s = str, 0);
}
