/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:00:47 by isb3              #+#    #+#             */
/*   Updated: 2024/08/21 10:38:52 by isb3             ###   ########.fr       */
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
	while (str[++j] && !is_del(str[j]) && !is_dollar_del(str[j]))
		;
	while (str[j])
		str_update[i++] = str[j++];
	str_update[i] = '\0';
	return (str_update);
}

int	is_dollar_in_double_quotes(char *s, int k, int i)
{
	int	token;

	token = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 39)
			token = !token;
		if (i == k && token)
			return (0);
		if (i == k && !token)
			return (1);
	}
	return (0);
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
			{
				if (arr[i][k] == '$' && (is_del(arr[i][k + 1]) || !arr[i][k
						+ 1]))
					k++;
				if (arr[i][k] == '$')
					if (is_dollar_in_double_quotes(arr[i], k, k))
						return (1);
			}
		}
	}
	if (token == 'p')
		return (is_dollar_utils(arr, i, k, pos));
	return (0);
}

void	get_dollar(char **arr, int i, int k, int j)
{
	char	*env_var;
	char	*new_str;

	i = is_dollar_in_arr(arr, -1, 'p', 'i');
	k = is_dollar_in_arr(arr, -1, 'p', 'k');
	if (k && !is_dollar_in_double_quotes(arr[i], k, k))
		return ;
	if (!arr[i][k + 1] || is_del(arr[i][k + 1]))
		return ;
	j = k;
	while (arr[i][++j] && !is_del(arr[i][j]) && !is_dollar_del(arr[i][j]))
		;
	env_var = ft_substr(arr[i], k + 1, j - k - 1);
	if (!ft_strncmp(&arr[i][k], "$?", 2))
	{
		return (arr[i] = ft_strjoin(ft_strjoin(ft_substr(arr[i], 0,
						ft_strlen(arr[i]) - ft_strlen(ft_strchr(arr[i], '$'))),
					ft_itoa(return_(0, GET))), &arr[i][k + 2]), (void)0);
	}
	else
		new_str = get_envv(0, env_var, FIND);
	if (!new_str)
		new_str = ft_strdup("\0");
	arr[i] = join_new_str(arr[i], new_str, j - k, 0);
}
