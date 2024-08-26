/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:28 by adesille          #+#    #+#             */
/*   Updated: 2024/08/26 16:26:43 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: checks if a character is a common separator.
 * 
 * @param c: 
 *
 * ⬅️ Return: t_bool, TRUE if the character is a separator, FALSE otherwise.
 */
t_bool	is_separator(const char c)
{
	return (c == SPACE || c == TAB || c == NEWLINE);
}

int	is_redir(char *s, int i, char token)
{
	if (token == '?')
	{
		i = -1;
		while (s[++i])
			if (s[i] == '<' || s[i] == '>')
				return (1);
	}
	if (s[i] == '<' && s[i + 1] != '<')
		return (1);
	else if (s[i] == '>' && s[i + 1] != '>')
		return (2);
	return (0);
}

int	is_there_quotes_in_da_shit(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == 34 || s[i] == 39)
			return (1);
	return (0);
}
