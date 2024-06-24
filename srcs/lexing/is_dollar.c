/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:00:47 by isb3              #+#    #+#             */
/*   Updated: 2024/06/24 08:29:22 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar_utils(char **arr, int i, int k, int pos)
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
	return (0);
}

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
		return (is_dollar_utils(arr, i, k, pos));
	return (0);
}

char	*join_new_str(char *str, char *new_str, int var_len)
{
	char	*str_update;
	int		new_len;
	int		i;
	int		k;
	int		j;

	i = 0;
	j = -1;
	new_len = ft_strlen(str) + ft_strlen(new_str) - var_len + 1;
	str_update = malloc(new_len);
	if (!str_update)
		return (NULL);
	while (str[++j] != '$')
		str_update[i++] = str[j];
	k = 0;
	printf("i = %d\n", i);
	while (new_str[k])
		str_update[i++] = new_str[k++];
	while (str[j] && !is_del(str[++j]))
		;
	while (str[j])
		str_update[i++] = str[++j];
	str_update[i] = '\0';
	free(str);
	return (str_update);
}

int	is_dollar_in_double_quotes(char *s, int k, int i)
{
	int	token1;
	int	token2;

	i = k;
	while (s[--i] && s[i] != 34 && s[i] != 39)
		;
	if (s[i] == 34 || s[i] == 39)
		token1 = s[i];
	while (s[++k] && s[k] != 34 && s[k] != 39)
		;
	if (s[k] == 34 || s[k] == 39)
		token2 = s[k];
	if (token1 && token2)
	{
		if (i < k)
		{
			if (token1 == 34)
				return (1);
		}
		else
			if (token2 == 34)
				return (1);
		return (0);
	}
	return (1);
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
	if (!is_dollar_in_double_quotes(arr[i], k, 0))
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
	arr[i] = join_new_str(arr[i], new_str, j - k);
	return (free(env_var), 0);
}
