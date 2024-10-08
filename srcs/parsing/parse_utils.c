/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:17:12 by adesille          #+#    #+#             */
/*   Updated: 2024/08/25 10:42:00 by isb3             ###   ########.fr       */
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

	new_s = mem_manager(strlen_minus_quotes(s, 0, 0, 0) + 1, 0, 0, ALLOCATE);
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

int	cmdlen(char **tokens, int *i)
{
	int	len;

	len = 0;
	while (tokens[*i] && !is_pipe(tokens[*i], 0, 0))
	{
		if (is_redir(tokens[*i], 0, 0))
			(*i) += 2;
		else if (ft_strlen(tokens[*i]))
		{
			(*i)++;
			len++;
		}
		else
			(*i)++;
	}
	return (len);
}

t_ast	*return_tail(t_ast *ast)
{
	if (!ast->next)
		return (ast);
	while (ast && ast->next)
		ast = ast->next;
	return (ast);
}

void	init_lst(t_ast **ast)
{
	(*ast)->cmd = NULL;
	(*ast)->cmd_path = NULL;
	(*ast)->error = NULL;
	(*ast)->error_code = 0;
	(*ast)->pid = 0;
	(*ast)->fd_in = 0;
	(*ast)->fd_out = 0;
}
