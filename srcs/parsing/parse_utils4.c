/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:03:01 by adesille          #+#    #+#             */
/*   Updated: 2024/07/03 10:07:01 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	format_check(char *s, int *code)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (printf("minihell: %s: numeric argument required\n", s), 1);
	}
	if (*code)
	{
		if (*code > 255)
			*code -= 256;
		else if (code < 0)
			*code = 256 - -*code;
	}
	return (0);
}

char	**extract_path(void)
{
	char	**path;
	char	*trimm_path;

	trimm_path = getenv("PATH");
	if (!trimm_path)
		return (NULL);
	path = ft_split(trimm_path, ':');
	return (path);
}

void	get_dollar_hd(t_heredoc *hd)
{
	char	*env_var;
	char	*new_str;
	int		i;
	int		k;

	while (hd)
	{
		while (is_dollar(hd->s, '?'))
		{
			i = is_dollar(hd->s, 0);
			k = i;
			while (!is_del(hd->s[k]) && hd->s[k] && hd->s[k] != 34
				&& hd->s[k] != 39)
				k++;
			env_var = ft_substr(hd->s, i + 1, k - i - 1);
			if (!ft_strncmp(&hd->s[i], "$?", 2))
				new_str = ft_itoa(g_error_code);
			else
				new_str = getenv(env_var);
			if (!new_str)
				new_str = ft_strdup("\0");
			hd->s = join_new_str(hd->s, new_str, k - i);
		}
		hd = hd->next;
	}
}
