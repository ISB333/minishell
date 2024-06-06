/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:33:30 by adesille          #+#    #+#             */
/*   Updated: 2024/06/06 12:49:06 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes(char **tokens)
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
int	find_close_quotes_pos(char *s, int n, char q)
{

}

int	quotes_manager(char **tokens)
{
	if (is_quotes(tokens))
	{
		printf("quotes\n");
		
	}
	return (0);
}