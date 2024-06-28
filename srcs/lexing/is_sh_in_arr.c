/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh_in_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 06:23:29 by isb3              #+#    #+#             */
/*   Updated: 2024/06/28 11:21:20 by adesille         ###   ########.fr       */
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

int	is_new_line_in_arr(char **array)
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
			if (array[i][k] == '\n' && array[i - 1][0] != '|')
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
		if (array[i][0] == '<')
			return (1);
		if (array[i][0] == '>')
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