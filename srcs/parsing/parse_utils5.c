/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:40:16 by adesille          #+#    #+#             */
/*   Updated: 2024/08/13 09:40:52 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_directory_utils(t_ast **ast)
{
	if ((access((*ast)->cmd[0], R_OK) || access((*ast)->cmd[0], X_OK))
		&& !ft_strncmp((*ast)->cmd[0], "./", 2))
	{
		(*ast)->error = error_init("Permission denied", (*ast)->cmd[0]);
		(*ast)->error_code = 126;
		return (return_(126, ADD), 126);
	}
	if (!access((*ast)->cmd[0], X_OK) && ((*ast)->cmd[0][0] == '.'
		|| (*ast)->cmd[0][0] == '/'))
	{
		(*ast)->cmd_path = ft_strdup((*ast)->cmd[0]);
		return (0);
	}
	else
	{
		(*ast)->error = error_init("command not found", (*ast)->cmd[0]);
		(*ast)->error_code = 127;
		return (return_(127, ADD), 127);
	}
	return (0);
}

long long	ft_atoi_ll(const char *nptr)
{
	int			i;
	int			sign;
	long long	nbr;

	sign = 1;
	i = 0;
	nbr = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nbr = (nbr * 10) + ((nptr[i++]) - 48);
	return (nbr * sign);
}
