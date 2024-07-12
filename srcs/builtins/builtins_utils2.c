/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:20:22 by isb3              #+#    #+#             */
/*   Updated: 2024/07/12 12:16:52 by isb3             ###   ########.fr       */
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
	while (envv)
	{
		if (!ft_strncmp(envv->var, to_find, ft_strlen(to_find)))
			return (ft_strchr(envv->var, '=') + 1);
		envv = envv->next;
	}
	return (NULL);
}

void	print_env(t_env *envv)
{
	while (envv)
	{
		printf("%s\n", envv->var);
		envv = envv->next;
	}
}
