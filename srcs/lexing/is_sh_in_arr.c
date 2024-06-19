/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh_in_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 06:23:29 by isb3              #+#    #+#             */
/*   Updated: 2024/06/19 09:33:35 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_in_arr(char **array)
{
	int	i;
	int	k;
	int	n;

	i = -1;
	n = 0;
	while (array[++i])
	{
		k = -1;
		while (array[i][++k])
		{
			if (array[i][k] == '|')
				n++;
		}
	}
	return (n);
}

int	is_redir_in_arr(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (0);
	while (array[++i])
	{
		if (array[i][0] == '<' && array[i][1] != '<')
			return (1);
		if (array[i][0] == '>' && array[i][1] != '>')
			return (2);
	}
	return (0);
}

int	is_append_in_arr(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (0);
	while (array[++i])
	{
		if (array[i][0] == '>' && array[i][1] == '>')
			return (1);
	}
	return (0);
}
