/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh_in_arr1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 06:23:29 by isb3              #+#    #+#             */
/*   Updated: 2024/07/16 09:47:50 by isb3             ###   ########.fr       */
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

int	is_dollar_utils(char **arr, int i, int k, int pos)
{
	while (arr[++i])
	{
		k = -1;
		while (arr[i][++k])
		{
			if (arr[i][k] == '$' && (is_del(arr[i][k + 1]) || !arr[i][k + 1]))
				k++;
			if (arr[i][k] == '$' && pos == 'i'
				&& is_dollar_in_double_quotes(arr[i], k, k))
				return (i);
			if (arr[i][k] == '$' && pos == 'k'
				&& is_dollar_in_double_quotes(arr[i], k, k))
				return (k);
		}
	}
	return (0);
}
