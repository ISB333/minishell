/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:41:47 by adesille          #+#    #+#             */
/*   Updated: 2024/07/06 14:35:57by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_export(t_export **exp, char *var)
{
	t_export *prev = *exp;
	t_export *curr = *exp;
	
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

int	modify_exp_var(t_export *exp, char *var)
{
	char *exp_var;

	while (exp)
	{
		exp_var = ft_strchr(exp->var, 'x') + 2;
		exp_var = ft_substr(exp_var, 0, ft_strlen(exp_var) - ft_strlen(ft_strchr(exp_var, '=')));
		if (!ft_strncmp(exp_var, var, ft_strlen(exp_var)))
		{
			exp->var = ft_strjoin("declare -x ", var);
			return (0);
		}
		exp = exp->next;
	}
	return (1);
}

void	exportt(char *env[], char *var, int token)
{
	static t_export	*exp;

	if (token == 'I')
		init_export(env, &exp);
	if (token == 'A')
	{
		if (!get_envv(0, var, 'A'))
			add_node_exp(&exp, ft_strjoin("declare -x ", var));
		else
			modify_exp_var(exp, var);
	}
	if (token == 'P')
		print_export(exp);
	if (token == 'U')
		unset_export(&exp, var);
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
