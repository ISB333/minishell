/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh_in_arr2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 06:23:29 by isb3              #+#    #+#             */
/*   Updated: 2024/07/05 10:23:35 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_del(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		else
			break ;
	}
	if (!s[i])
		return (1);
	return (0);
}

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
			if (array[i][k] == '|' && array[i + 1])
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

int	is_local_var_in_arr(char **arr, int i, int k, int token)
{
	if (token == '?')
	{
		while (arr[++i])
		{
			k = -1;
			while (arr[i][++k])
				if (arr[i][k] == '=' && !is_there_quotes_in_da_shit(arr[i])
					&& ft_isalpha(arr[i][k - 1]))
					return (1);
		}
	}
	else if (token == 'y')
	{
		if (arr[i])
			while (arr[i][++k])
			{
				if (arr[i][k] == '=' && !is_there_quotes_in_da_shit(arr[i])
					&& ft_isalpha(arr[i][k - 1]))
					return (1);
				if (arr[i][k] == '=' && is_there_quotes_in_da_shit(arr[i])
					&& !ft_isalpha(arr[i][k - 1]))
					return (0);
			}
	}
	else
	{
		if (arr[i])
			while (arr[i][++k])
				if (arr[i][k] == '=')
					return (1);
	}
	return (0);
}

int	is_local_var(char *s)
{
	int	i;

	i = -1;
	if (s)
		while (s[++i])
			if (s[i] == '=')
				return (1);
	return (0);
}

int	is_only_local_var(char **arr, int i, int k, int token)
{
	int	true_token;

	while (arr[0][++k])
		if (arr[0][k] == '=' && !is_there_quotes_in_da_shit(arr[0])
			&& ft_isalpha(arr[0][k - 1]))
			token = 1;
	if (!token)
		true_token = 0;
	else
		true_token = 1;
	if(arr[1])
	{
		token = 0;
		while (arr[++i])
		{
			if (is_local_var_in_arr(arr, i, -1, 'y'))
					token = 1;
			if (token != true_token)
				return (true_token);
		}
	}
	return (true_token);
}
