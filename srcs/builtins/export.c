/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:57:47 by nkieffer          #+#    #+#             */
/*   Updated: 2024/06/27 16:56:10 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	ft_export(char **my_env, char *var)
// {
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	while (my_env[i] != NULL)
// 		i++;
// 	i++;
// 	new_env = malloc((i + 1) * sizeof(char *));
// 	new_env[i] = NULL;
// 	i = 0;
// 	while (my_env[i] != NULL)
// 	{
// 		new_env[i] = my_env[i];
// 		i++;
// 	}
// 	new_env[i] = ft_strdup(var);
// 	free(my_env);
// 	return (new_env);
// }
