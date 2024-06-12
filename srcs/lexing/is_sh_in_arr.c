/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sh_in_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 06:23:29 by isb3              #+#    #+#             */
/*   Updated: 2024/06/12 10:43:39 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_in_arr(char **array)
{
	int	i;
	int k;
	int	n;
	
	i = -1;
	n = 0;
	while(array[++i])
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
	while(array[++i])
	{
		if (array[i][0] == '<' && array[i][1] != '<')
			return (1);
		if (array[i][0] == '>' && array[i][1] != '>')
			return (2);
	}
	return (0);
}
