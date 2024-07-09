/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:41:47 by adesille          #+#    #+#             */
/*   Updated: 2024/07/09 06:07:32 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_export(t_export **exp, char *var)
{
	t_export	*prev;
	t_export	*curr;

	prev = *exp;
	curr = *exp;
	if (!ft_strncmp(ft_strchr((*exp)->var, 'x') + 2, var, ft_strlen(var)))
		*exp = (*exp)->next;
	else
	{
		prev = curr;
		curr = curr->next;
		while (curr)
		{
			if (!ft_strncmp(ft_strchr(curr->var, 'x') + 2, var, ft_strlen(var)))
			{
				prev->next = curr->next;
				return ;
			}
			prev = curr;
			curr = curr->next;
		}
	}
}

void	exportt(char *env[], char *var, int token)
{
	static t_export	*exp;

	if (token == INIT)
		init_export(env, &exp);
	if (token == ADD)
	{
		if (!get_envv(0, var, ADD))
		{
			add_node_exp(&exp, ft_strjoin("declare -x ", var));
			sort_export(exp);
		}
		else
			modify_exp_var(exp, var);
	}
	if (token == PRINT)
		print_export(exp);
	if (token == UNSET)
		unset_export(&exp, var);
}

void	echoo(char **arr)
{
	int	i;
	int	token;

	token = 0;
	i = 0;
	while (!ft_strncmp(arr[++i], "-n", 2))
	{
		if (is_only_n(arr[i]))
			token = 1;
		else
			break ;
	}
	if (arr)
	{
		while (arr[i])
		{
			printf("%s", arr[i]);
			if (arr[++i])
				printf(" ");
		}
		if (!token)
			printf("\n");
	}
	else
		printf("\n");
}

void	pwdd(void)
{
	printf("%s\n", get_cwdd(0, 0, GET));
}

int	cd(char **arr)
{
	if (!arr[1])
	{
		if (chdir(ft_strjoin("/home/", get_envv(0, "USER", FIND))))
			return (-1);
	}
	else
	{
		if (chdir(arr[1]))
			return (-1);
	}
	get_cwdd(0, arr[1], UPDATE);
	return (0);
}
