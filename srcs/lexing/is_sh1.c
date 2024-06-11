/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:48:52 by adesille          #+#    #+#             */
/*   Updated: 2024/06/11 12:06:28 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_append(char *s, int i, char token)
{
	if (token == '?')
	{
		i = -1;
		while (s[++i])
			if (s[i] == '>' || s[i + 1] == '>')
				return (1);
	}
	else if (s[i] == '>' || s[i + 1] == '>')
		return (1);
	return (0);
}

int	is_heredoc(char *s, int i, char token)
{
	if (token == '?')
	{
		i = -1;
		while (s[++i])
			if (s[i] == '<' || s[i + 1] == '<')
				return (1);
	}
	else if (s[i] == '<' || s[i + 1] == '<')
		return (1);
	return (0);
}

int	is_pipe(char *s, int i, char token)
{
	if (token == '?')
	{
		i = -1;
		while (s[++i])
		{
			if (s[i] == '|')
				return (1);
			if (s[i] == '|' || s[i + 1] == '|')
				return (2);
		}
	}
	else if (s[i] == '|' && s[i + 1] == '|')
		return (2);
	else if (s[i] == '|')
		return (1);
	return (0);
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
