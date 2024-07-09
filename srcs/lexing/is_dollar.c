/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:00:47 by isb3              #+#    #+#             */
/*   Updated: 2024/07/09 06:05:52 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar(char *s, int token)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '$')
		{
			if (token == '?')
				return (1);
			return (i);
		}
	}
	return (0);
}

char	*join_new_str(char *str, char *new_str, int var_len, int i)
{
	char	*str_update;
	int		new_len;
	int		k;
	int		j;

	j = 0;
	if (!str)
		return (NULL);
	new_len = ft_strlen(str) - var_len + ft_strlen(new_str) + 1;
	str_update = mem_manager(new_len, 0, 0, 'A');
	while (str[j] != '$')
	{
		str_update[i++] = str[j++];
		if (str[j] == '$' && !is_dollar_in_double_quotes(str, j, j))
			str_update[i++] = str[j++];
	}
	k = 0;
	while (new_str[k])
		str_update[i++] = new_str[k++];
	while (str[j] && !is_del(str[j]) && str[j] != 39 && str[j] != 34)
		j++;
	while (str[j])
		str_update[i++] = str[j++];
	str_update[i] = '\0';
	return (str_update);
}

int	is_dollar_in_double_quotes(char *s, int k, int i)
{
	int	token2;
	int	token1;

	token2 = 0;
	token1 = 0;
	while (i > 0 && s[i] && s[i] != 34 && s[i] != 39)
		i--;
	if (i > 0 && s[i] && (s[i] == 34 || s[i] == 39))
		token1 = s[i];
	while (s[k] && s[k] != 34 && s[k] != 39)
		k++;
	if (s[k] == 34 || s[k] == 39)
		token2 = s[k];
	if (token1 && token2)
	{
		if (i < k)
		{
			if (token1 == 34)
				return (1);
		}
		else if (token2 == 34)
			return (1);
		return (0);
	}
	return (1);
}

int	is_dollar_in_arr(char **arr, int i, char token, char pos)
{
	int	k;

	if (token == '?')
	{
		while (arr[++i])
		{
			k = -1;
			while (arr[i][++k])
				if (arr[i][k] == '$')
					if (is_dollar_in_double_quotes(arr[i], k, k))
						return (1);
		}
	}
	if (token == 'p')
		return (is_dollar_utils(arr, i, k, pos));
	return (0);
}

void	get_dollar(char **arr)
{
	char	*env_var;
	char	*new_str;
	int		i;
	int		k;
	int		j;

	i = is_dollar_in_arr(arr, -1, 'p', 'i');
	k = is_dollar_in_arr(arr, -1, 'p', 'k');
	if (k)
		if (!is_dollar_in_double_quotes(arr[i], k, k))
			return ;
	j = k;
	while (!is_del(arr[i][j]) && arr[i][j] && arr[i][j] != 34
		&& arr[i][j] != 39)
		j++;
	env_var = ft_substr(arr[i], k + 1, j - k - 1);
	if (!ft_strncmp(&arr[i][k], "$?", 2))
		new_str = ft_itoa(g_error_code);
	else
		new_str = get_envv(0, env_var, FIND);
	if (!new_str)
		new_str = ft_strdup("\0");
	arr[i] = join_new_str(arr[i], new_str, j - k, 0);
}
