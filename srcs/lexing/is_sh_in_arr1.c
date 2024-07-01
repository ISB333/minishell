/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh_in_arr1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 06:23:29 by isb3              #+#    #+#             */
/*   Updated: 2024/07/01 10:36:42 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_heredoc_in_arr(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (0);
	while (array[++i])
	{
		if (array[i][0] == '<' && array[i][1] == '<')
			return (1);
	}
	return (0);
}

int	is_open_pipe_in_arr_arr(char ***array)
{
	int	i;
	int	k;

	k = -1;
	i = -1;
	if (!array)
		return (0);
	while (array[++i])
	{
		k = -1;
		while (array[i][++k])
			if (array[i][k][0] == '|' && !array[i + 1])
				return (1);
	}
	return (0);
}

int	is_open_pipe_in_arr(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (0);
	while (array[++i])
	{
		if (array[i][0] == '|' && !array[i + 1])
			return (1);
	}
	return (0);
}
