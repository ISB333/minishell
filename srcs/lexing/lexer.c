/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/11 12:30:56 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_quotes(char *s)
{
	int	i;
	int	k;
	int	token;

	i = 0;
	k = 0;
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

int	array_len(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		;
	return (i);
}

char	**lexer(char *s)
{
	char	**tokens;
	size_t	i;

	if (!s)
		return (NULL);
	if (is_sh_ope(s, 0, '?'))
		if (add_space(&s, 0, 0, 0))
			return (free(s), NULL);
	if (open_quotes(s))
		return (free(s), \
			printf("Brother, I will smash ur face. Close me dat quote!\n"), \
				NULL);
	tokens = (char **)malloc((count_rows(s, 0) + 1) * sizeof(char *));
	tokens = splitter(tokens, s);
	if (!tokens)
		return (free(s), NULL);
	i = -1;
	while (tokens[++i])
		printf("%zu = %s\n", i, tokens[i]);
	return (free(s), tokens);
}
