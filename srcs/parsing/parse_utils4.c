/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:03:01 by adesille          #+#    #+#             */
/*   Updated: 2024/07/11 08:00:22 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_check_utils(t_ast *ast)
{
	int	code;

	while (ast->next)
		ast = ast->next;
	if (ast->cmd && !ft_strcmp(ast->cmd[0], "exit\0"))
	{
		code = ft_atoi(ast->cmd[1]);
		if (ast->cmd[1])
		{
			if (format_check(ast->cmd[1], &code))
				return (mem_manager(0, 0, 0, 'C'), exit(2));
			return (mem_manager(0, 0, 0, 'C'), exit(code));
		}
		return (mem_manager(0, 0, 0, 'C'), exit(EXIT_SUCCESS));
	}
}

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
			return (error("numeric argument required", s, 2));
	}
	if (*code)
	{
		if (*code > 255)
			*code -= 256;
		else if (*code < 0)
			*code = 256 - -*code;
	}
	return (0);
}

char	**extract_path(void)
{
	char	**path;
	char	*trimm_path;

	trimm_path = get_envv(0, "PATH", FIND);
	if (!trimm_path)
		return (NULL);
	path = ft_split(trimm_path, ':');
	return (path);
}

void	get_dollar_hd(t_heredoc *hd)
{
	char	*env_var;
	char	*new_str;
	int		k;
	int		j;

	while (hd)
	{
		while (is_dollar(hd->s, '?'))
		{
			k = is_dollar(hd->s, 0);
			j = k;
			while (!is_del(hd->s[j]) && hd->s[j] && hd->s[j] != 34
				&& hd->s[j] != 39)
				j++;
			env_var = ft_substr(hd->s, k + 1, j - k - 1);
			if (!ft_strncmp(&hd->s[k], "$?", 2))
				new_str = ft_itoa(g_error_code);
			else
				new_str = get_envv(0, env_var, FIND);
			if (!new_str)
				new_str = ft_strdup("\0");
			hd->s = join_new_str(hd->s, new_str, j - k, 0);
		}
		hd = hd->next;
	}
}
