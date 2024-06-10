/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:00:47 by isb3              #+#    #+#             */
/*   Updated: 2024/06/09 09:47:10 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar(char **arr, int i, char token, char pos)
{
	int	k;

	if (token == '?')
	{
		while (arr[++i])
		{
			k = -1;
			while (arr[i][++k])
				if (arr[i][k] == '$')
					return (1);
		}
	}
	if (token == 'p')
	{
		while (arr[++i])
		{
			k = -1;
			while (arr[i][++k])
			{
				if (arr[i][k] == '$' && pos == 'i')
					return (i);
				if (arr[i][k] == '$' && pos == 'k')
					return (k);
			}
		}
	}
	return (0);
}

char	*join_new_str(char *str, char *new_str, int var_len)
{
	char	*str_update;
	int		new_len;
	int		i;
	int		k;

	i = -1;
	new_len = ft_strlen(str) + ft_strlen(new_str) - var_len + 2;
	str_update = malloc(new_len);
	if (!str_update)
		return (NULL);
	while (str[++i] != '$')
		str_update[i] = str[i];
	k = 0;
	while (new_str[k])
		str_update[i++] = new_str[k++];
	while (str[i++])
		str_update[i] = str[i];
	str_update[i] = '\0';
	free(str);
	return (str_update);
}

int	get_dollar(char **arr)
{
	char	*env_var;
	char	*new_str;
	int		i;
	int		k;
	int		j;

	i = is_dollar(arr, -1, 'p', 'i');
	k = is_dollar(arr, -1, 'p', 'k');
	if (arr[i][0] == 39)
		return (0);
	j = k;
	while (!is_del(arr[i][j]) && arr[i][j] && arr[i][j] != 34
		&& arr[i][j] != 39)
		j++;
	if (arr[i][j - 1] == 34)
		j--;
	env_var = ft_substr(arr[i], k + 1, j - k - 1);
	new_str = getenv(env_var);
	if (!new_str)
		return (free(env_var), 1);
	arr[i] = join_new_str(arr[i], new_str, j - k - 1);
	return (free(env_var), 0);
}