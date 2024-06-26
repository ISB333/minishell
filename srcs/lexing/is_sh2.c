/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:04:28 by adesille          #+#    #+#             */
/*   Updated: 2024/06/26 11:58:18 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_del(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
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

int	is_new_line(char **tokens, int i)
{
	// int	k = 0;
	// while(tokens[i][k])
	// {
	// 	// printf("%c", tokens[i][k]);
	if (tokens && tokens[i])
		if (tokens[i][0] == '\n' && tokens[i - 1][0] != '|')
			return (1);
	// 	k++;
	// }
	return (0);
}
