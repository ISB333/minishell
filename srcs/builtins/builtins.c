/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:41:47 by adesille          #+#    #+#             */
/*   Updated: 2024/08/06 10:20:16 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_exist_exp(t_export *exp, char *var)
{
	char	*exp_var;

	if (ft_strchr(var, '='))
		var = ft_substr(var, 0, ft_strlen(var) - ft_strlen(ft_strchr(var,
						'=')));
	while (exp)
	{
		if (ft_strchr(exp->var, '='))
			exp_var = ft_substr(exp->var, 0, ft_strlen(exp->var)
					- ft_strlen(ft_strchr(exp->var, '=')));
		else
			exp_var = ft_strdup(exp->var);
		if (!ft_strcmp(exp_var, var))
			return (1);
		exp = exp->next;
	}
	return (0);
}

void	unset_export(t_export **exp, char *var)
{
	t_export	*tmp;

	if (!var)
		return ;
	tmp = *exp;
	if (!ft_strncmp((*exp)->var, var, ft_strlen(var)))
		*exp = (*exp)->next;
	else
	{
		while (tmp)
		{
			if (tmp->next && !ft_strncmp(tmp->next->var, var, ft_strlen(var)))
			{
				tmp->next = tmp->next->next;
				break ;
			}
			tmp = tmp->next;
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
		if (!var)
			return ;
		if (!get_envv(0, var, ADD) && env_format_check(var)
			&& !check_if_exist_exp(exp, var))
		{
			add_node_exp(&exp, var);
			sort_export(exp);
		}
		else if (!env_format_check(var))
			error("not a valid identifier", ft_strjoin("export: ", var), 1);
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
	while (arr[++i] && !ft_strncmp(arr[i], "-n", 2))
	{
		if (is_only_n(arr[i]))
			token = 1;
		else
			break ;
	}
	if (arr[i])
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
	else if (!token)
		printf("\n");
}

void	pwdd(void)
{
	printf("%s\n", get_cwdd(0, 0, GET));
}

int	cd(char **arr)
{
	struct stat	path_stat;
	char		*dir;

	if ((arr[1] && arr[2]))
		return (error("too many arguments", "cd", 1));
	if (arr[1] && ft_strchr(arr[1], '/'))
		dir = ft_substr(arr[1], 0, ft_strlen(arr[1])
				- ft_strlen(ft_strchr(arr[1], '/')));
	else if (arr[1])
		dir = ft_strdup(arr[1]);
	if (!stat(dir, &path_stat) && !S_ISDIR(path_stat.st_mode))
		return (error("Not a directory", ft_strjoin("cd: ", arr[1]), 1));
	if (!arr[1] || !ft_strcmp(arr[1], "~"))
	{
		if (chdir(get_cwdd(0, 0, HOME)))
			return (printf("thefuck\n"), -1);
	}
	else
	{
		if (arr[1] && (!ft_strlen(arr[1]) || !ft_strcmp(arr[1], ".")))
			return (0);
		if (arr[1][0] == '~')
			arr[1] = ft_strjoin(get_cwdd(0, 0, HOME), arr[1] + 1);
		if (!access(arr[1], OK) && access(arr[1], X_OK))
			return (error("Permission denied", "cd", 1));
		if (chdir(arr[1]))
			return (error("No such file or directory", ft_strjoin("cd: ",
						arr[1]), 1));
	}
	get_cwdd(0, arr[1], UPDATE);
	return (0);
}
