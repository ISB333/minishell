/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:13:17 by adesille          #+#    #+#             */
/*   Updated: 2024/06/17 09:30:23 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mem(char **array, size_t j)
{
	while (j-- > 0)
		free(array[j]);
	free(array);
}

int	open_quotes(char *s)
{
	int	i;
	int	token;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			if (!s[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	array_len(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		;
	return (i);
}
