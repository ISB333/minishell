/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:48:52 by adesille          #+#    #+#             */
/*   Updated: 2024/06/10 14:39:15 by adesille         ###   ########.fr       */
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
	else if (s[i] == '<' || s[i] == '>')
		return (1);
	return (0);
}

int	is_sh_ope(char *s, int i, char token)
{
	if (token == '?')
	{
		i = -1;
		while (s[++i])
		{
			if (s[i] == '|' || (s[i] == '<' && s[i + 1] != '<')
				|| (s[i] == '>' && s[i + 1] != '>'))
				return (1);
			if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>'
					&& s[i + 1] == '>'))
				return (2);
		}
	}
	else
	{
		if (s[i] == '|' || (s[i] == '<' && s[i + 1] != '<')
			|| (s[i] == '>' && s[i + 1] != '>'))
			return (1);
		if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>'
				&& s[i + 1] == '>'))
			return (2);
	}
	return (0);
}

int	closing_quotes_pos(char *s, int i)
{
	if (s[i] == 34)
	{
		i++;
		while (s[i] && s[i] != 34)
			i++;
		return (i + 1);
	}
	if (s[i] == 39)
	{
		i++;
		while (s[i] && s[i] != 39)
			i++;
	}
	return (i + 1);
}

int	find_closing_quote(char *s, int i, char c)
{
	if (c == 34)
	{
		while (s[i])
		{
			if (s[++i] == 34)
				return (1);
		}
		return (34);
	}
	if (c == 39)
	{
		while (s[i])
		{
			if (s[++i] == 39)
				return (1);
		}
	}
	return (39);
}

int	is_quotes(char *s, int i, char token)
{
	if (token == '?')
	{
		token = s[i++];
		while (s[i] && s[i] != token)
			i++;
		return (i);
	}
	if (s[i] == 34 || s[i] == 39)
		return (printf("quote found = %c\n", s[i+2]), 1);
	return (0);
}
