/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:33:30 by adesille          #+#    #+#             */
/*   Updated: 2024/06/07 07:54:50 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_this_quotes(char **tokens)
{
	int	i;
	int	k;

	i = -1;
	while (tokens[++i])
	{
		k = -1;
		while (tokens[i][++k])
		{
			if (tokens[i][k] == 34 || tokens[i][k] == 39)
				return (1);
		}
	}
	return (0);
}
// int	find_close_quotes_pos(char *s, int n, char q)
// {

// 	return (0);
// }

int join_quotes(char **tokens, int i)
{
	char	*new_str;

	new_str = ft_strjoin(tokens[i], tokens[i + 1]);
	if (!new_str)
		return (1);
	free(tokens[i]);
	tokens[i] = new_str;
	tokens[i + 1][0] = '\0';
	return (0);
}

int	find_and_join(char **tokens, int i, int k, char q)
{
	while (tokens[i])
	{
		while (tokens[i][k] != q && tokens[i][k])
			k++;
		if (tokens[i][k] == q)
		{
			if (join_quotes(tokens, i))
				return (1);
			break;	
		}
		else
		{
			if (join_quotes(tokens, i))
				return (1);
			k = -1;
		}
	}
	return (0);
}

int	is_quotes_inside(char *s, int i, char token)
{
	if (!s[i])
		return (0);
	while (s[++i])
	{
		if (s[i] == 34 && token == 34)
			return (1);
		if (s[i] == 39 && token == 39)
			return (1);
	}
	return (0);
}

int	quotes_manager(char **tokens)
{
	int	i;
	int	k;

	i = -1;
	// if (is_this_quotes(tokens))
	// {
	// 	printf("quotes\n");
	// }
	while (tokens[++i])
	{
		k = -1;
		while (tokens[i][++k])
		{
			if (is_quotes(tokens[i], k, 0)) 
			{
				if(!is_quotes_inside(tokens[i], tokens[i][k], k + 1))
				{
					if (find_and_join(tokens, i, k, tokens[i][k]))
						return (1);
				}
			}
		}
		printf("%s\n", tokens[i]);
	}
	return (0);
}