/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:13:17 by adesille          #+#    #+#             */
/*   Updated: 2024/08/15 12:56:08 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_quotes(char *s)
{
	int	i;
	int	token;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			if (!s[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	is_dollar_del(char c)
{
	if (c == '$' || c == '/' || c == '|' || c == 34 || c == 39)
		return (1);
	return (0);
}

int	array_len(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
		i++;
	return (i);
}

char	*open_pipe_manager(void)
{
	char		*s;
	char		*str;

	while (1)
	{
		s = readline("> ");
		str = ft_strdup(s);
		free(s);
		if (str)
		{
			return (str);
		}
	}
	return (NULL);
}

int	is_builtin(t_ast *ast)
{
	if (!ast || !ast->cmd)
		return (0);
	if (!ft_strcmp(ast->cmd[0], "cd"))
		return (CD);
	if (!ft_strcmp(ast->cmd[0], "pwd"))
		return (PWD);
	if (!ft_strcmp(ast->cmd[0], "export"))
		return (EXPORT);
	if (!ft_strcmp(ast->cmd[0], "unset"))
		return (UNSET);
	if (!ft_strcmp(ast->cmd[0], "env"))
		return (ENV);
	if (!ft_strcmp(ast->cmd[0], "echo"))
		return (ECH);
	if (!ft_strcmp(ast->cmd[0], "exit"))
		return (EXIT);
	return (0);
}
