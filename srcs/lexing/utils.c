/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:13:17 by adesille          #+#    #+#             */
/*   Updated: 2024/08/21 10:38:42 by isb3             ###   ########.fr       */
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
	char	*s;
	char	*str;

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
