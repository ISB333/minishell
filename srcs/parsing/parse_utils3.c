/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:17:12 by adesille          #+#    #+#             */
/*   Updated: 2024/06/19 09:00:50 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fds_len(char **tokens, int *out_len, int *app_len, int *in_len)
{
	int	i;

	i = 0;
	while (tokens[i] && tokens[i][0] != '|')
	{
		if (is_redir(tokens[i], 0, 0) == 1)
		{
			i++;
			(*in_len)++;
		}
		if (is_redir(tokens[i], 0, 0) == 2)
		{
			i++;
			(*out_len)++;
		}
		if (is_append(tokens[i], 0, 0))
		{
			i += 2;
			(*app_len)++;
		}
		else
			i++;
	}
}

int	strlen_minus_quotes(char *s, int token, int len)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
			i++;
			len += 2;
		}
		if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				i++;
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

	new_s = malloc(strlen_minus_quotes(s, 0, 0) + 1);
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == 34)
		{
			token = s[i++];
			while (s[i] && s[i] != token)
				new_s[k++] = s[i++];
			i++;
		}
		if (s[i] == 39)
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
	while (tokens[*i] && !is_pipe(tokens[*i], 0, 0))
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
