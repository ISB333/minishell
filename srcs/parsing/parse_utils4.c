/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:03:01 by adesille          #+#    #+#             */
/*   Updated: 2024/07/13 06:22:22 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_directory_utils(t_ast **ast)
{
	if ((access((*ast)->cmd[0], R_OK) || access((*ast)->cmd[0], X_OK))
		&& !ft_strncmp((*ast)->cmd[0], "./", 2))
	{
		(*ast)->error = error_init("Permission denied", (*ast)->cmd[0]);
		(*ast)->error_code = 126;
		return (return_(126, ADD), 126);
	}
	if (!access((*ast)->cmd[0], X_OK) && (*ast)->cmd[0][0] == '.')
	{
		(*ast)->cmd_path = ft_strdup((*ast)->cmd[0]);
		return (0);
	}
	else
	{
		(*ast)->error = error_init("command not found", (*ast)->cmd[0]);
		(*ast)->error_code = 127;
		return (return_(127, ADD), 127);
	}
	return (0);
}

int	check_if_directory(t_ast **ast)
{
	struct stat	path_stat;

	if (stat((*ast)->cmd[0], &path_stat) != 0
		&& (!ft_strncmp((*ast)->cmd[0], "./", 2)
			|| (*ast)->cmd[0][0] == '/') && access((*ast)->cmd[0], OK))
	{
		(*ast)->error = error_init("No such file or directory", (*ast)->cmd[0]);
		(*ast)->error_code = 127;
		return (return_(127, ADD), 127);
	}
	if ((!ft_strncmp((*ast)->cmd[0], "/", 1)
			|| !ft_strncmp((*ast)->cmd[0], "./", 2))
		&& S_ISDIR(path_stat.st_mode))
	{
		(*ast)->error = error_init("Is a directory", (*ast)->cmd[0]);
		(*ast)->error_code = 126;
		return (return_(126, ADD), 126);
	}
	else
		return (check_if_directory_utils(ast));
	return (0);
}

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
				new_str = ft_itoa(return_(0, GET));
			else
				new_str = get_envv(0, env_var, FIND);
			if (!new_str)
				new_str = ft_strdup("\0");
			hd->s = join_new_str(hd->s, new_str, j - k, 0);
		}
		hd = hd->next;
	}
}
