/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:22:01 by nkieffer          #+#    #+#             */
/*   Updated: 2024/07/04 07:08:25 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Need to check '' and ""

int	ft_echo(t_ast *data)
{
	int	is_n;
	int	i;

	is_n = 0;
	i = 1;
	if (ft_strcmp(data->cmd[1], "-n") == 0)
	{
		is_n = 1;
		i++;
	}
	while (data->cmd[i] != NULL)
	{
		if ((is_n == 0 && i != 1) || (is_n == 1 && i != 2))
			write(1, " ", 1);
		write(1, data->cmd[i], ft_strlen(data->cmd[i]));
		i++;
	}
	if (is_n == 0)
		write(1, "\n", 1);
	return (0);
}
