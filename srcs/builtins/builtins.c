/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:41:47 by adesille          #+#    #+#             */
/*   Updated: 2024/07/06 08:22:29 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : echo (with -n option)
// TODO : cd

void	echoo(char **arr)
{
	int i = 0;

	if (arr)
	{
		while (arr[++i])
			printf("%s ", arr[i]);
		printf("\n");
	}
	else
		printf("\n");
}

void	pwdd()
{
	printf("%s\n", get_cwdd(0, 0, 'G'));
}

int	cd(char **arr)
{
	// Check if the arg are correct
	if (!arr[1])
	{
		if (chdir(ft_strjoin("/home/", get_envv(0, "USER", 'F'))))
			return (-1);
	}
	else
	{
		if (chdir(arr[1]))
			return (-1);
	}
	get_cwdd(0, arr[1], 'U');
	return (0);
}
