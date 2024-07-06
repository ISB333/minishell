/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:41:47 by adesille          #+#    #+#             */
/*   Updated: 2024/07/06 12:14:11 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : echo (with -n option)
// TODO : cd

void	exportt(char *env[], char *new_var, int token)
{
	static t_export	*exp;

	if (token == 'I')
		init_export(env, &exp);
	if (token == 'A')
		add_node_exp(&exp, ft_strjoin("declare -x ", new_var));
	if (token == 'P')
		print_export(exp);
}

void	echoo(char **arr)
{
	int	i;
	int	token;

	token = 0;
	i = 1;
	while (!ft_strncmp(arr[i], "-n", 2))
	{
		token = 1;
		i++;
	}
	if (arr)
	{
		while (arr[i])
			printf("%s", arr[i++]);
		if (arr[i + 1])
			printf(" ");
		if (!token)
			printf("\n");
	}
	else
		printf("\n");
}

void	pwdd(void)
{
	printf("%s\n", get_cwdd(0, 0, 'G'));
}

int	cd(char **arr)
{
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
