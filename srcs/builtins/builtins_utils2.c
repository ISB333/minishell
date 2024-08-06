/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:20:22 by isb3              #+#    #+#             */
/*   Updated: 2024/08/06 10:20:28 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quit(int token)
{
	if (token == EXIT_FAILURE)
	{
		mem_manager(0, 0, 0, 'C');
		exit(EXIT_FAILURE);
	}
	if (token == EXIT_SUCCESS)
	{
		mem_manager(0, 0, 0, 'C');
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	count_dir(char *cwd)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	if (!cwd)
		return (0);
	while (cwd[++i])
		if (cwd[i] == '/')
			len++;
	return (++len);
}

char	*env_var_search(t_env *envv, char *to_find)
{
	char	*envv_var;

	while (envv)
	{
		envv_var = ft_substr(envv->var, 0, ft_strlen(envv->var)
				- ft_strlen(ft_strchr(envv->var, '=')));
		if (!ft_strcmp(envv_var, to_find))
			return (ft_strchr(envv->var, '=') + 1);
		envv = envv->next;
	}
	return (NULL);
}

void	*print_or_get_env(t_env *envv, int token)
{
	int		len;
	char	**env;
	t_env	*tmp;

	tmp = envv;
	len = 0;
	while (envv)
	{
		if (token == PRINT)
			printf("%s\n", envv->var);
		len++;
		envv = envv->next;
	}
	if (token == GET)
	{
		env = mem_manager((len + 1) * sizeof(char *), 0, 0, 'A');
		env[len] = NULL;
		while (tmp)
		{
			env[len++] = tmp->var;
			tmp = tmp->next;
		}
		return (env);
	}
	return (NULL);
}
