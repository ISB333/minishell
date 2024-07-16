/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:00:47 by isb3              #+#    #+#             */
/*   Updated: 2024/07/16 09:13:08 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tilde_in_arr(char **arr, int i, char token)
{
	if (token == '?')
	{
		while (arr[++i])
		{
			if (arr[i][0] == '~' && (!arr[i][1] || arr[i][1] == '/'))
				return (1);
		}
	}
	if (token == 'p')
	{
		while (arr[++i])
		{
			if (arr[i][0] == '~' && (!arr[i][1] || arr[i][1] == '/'))
				return (i);
		}
	}
	return (0);
}

void	get_tilde(char **arr)
{
	int		i;

	i = is_tilde_in_arr(arr, -1, 'p');
	arr[i] = ft_strjoin(get_cwdd(0, 0, HOME), &arr[i][1]);
}
