/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:02:33 by isb3              #+#    #+#             */
/*   Updated: 2024/08/23 09:00:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_format_check(char *var)
{
	int	i;

	i = -1;
	if (!ft_isalpha(var[0]))
		return (0);
	while (var[++i] && var[i] != '=')
		if (var[i] != '=' && !ft_isalnum(var[i]) && var[i] != '_')
			return (0);
	return (1);
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

void	*print_or_get_env(t_env *envv, int token, int len)
{
	char	**env;
	t_env	*tmp;

	tmp = envv;
	while (envv)
	{
		if (token == PRINT)
			printf("%s\n", envv->var);
		len++;
		envv = envv->next;
	}
	if (token == GET)
	{
		env = mem_manager((len + 1) * sizeof(char *), 0, 0, ALLOCATE);
		env[len] = NULL;
		len = 0;
		while (tmp)
		{
			env[len++] = tmp->var;
			tmp = tmp->next;
		}
		return (env);
	}
	return (NULL);
}
