/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:17:12 by adesille          #+#    #+#             */
/*   Updated: 2024/06/27 13:35:29 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_minus_quotes(char *s, int token, int len, int i)
{
	while (s[i])
	{
		if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			if (s[i] == token)
				i++;
			len += 2;
		}
		else if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			if (s[i] == token)
				i++;
			len += 2;
		}
		else
			i++;
	}
	return (i - len);
}

char	*quotes_destroyer(char *s, int i, int k, int token)
{
	char	*new_s;

	new_s = mem_manager(strlen_minus_quotes(s, 0, 0, 0) + 1, 0, 'A');
	while (s[i])
	{
		if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				new_s[k++] = s[i++];
			i++;
		}
		else if (s[i] == 39)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				new_s[k++] = s[i++];
			i++;
		}
		else
			new_s[k++] = s[i++];
	}
	return (new_s[k] = '\0', new_s);
}

int	strlen_cmd(char **tokens, int *i)
{
	int	len;

	len = 0;
	while (tokens[*i] && !is_pipe(tokens[*i], 0, 0) && !is_new_line(tokens, *i))
	{
		if (is_redir(tokens[*i], 0, 0))
			(*i) += 2;
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

int	parse_append(t_ast **ast, char **tokens, int *i)
{
	char	*fd;

	if (is_there_quotes_in_da_shit(tokens[*i + 1]))
		fd = quotes_destroyer(tokens[*i + 1], 0, 0, 0);
	else
		fd = ft_substr(tokens[*i + 1], 0, ft_strlen(tokens[*i + 1]));
	printf("fd_append = %s\n", fd);
	(*ast)->fd_out = open(fd, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*ast)->fd_out == -1)
		return (printf(RED"error while opening: %s\n"DEF, fd), 1);
	(*ast)->append = 1;
	mem_manager(sizeof(int), (*ast)->fd_out, 'O');
	*i += 2;
	return (0);
}
