/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/07 13:50:33 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	- cmd {args}
	- redir cmd {args}
	- cmd {args} (redir || pipe)

	- l"s" -'l'"A"
		-> both ignored
	- echo "y"'ol'o
		-> same

	- echo '$USER'
		-> $USER
	- echo "$USER"
		-> adesille
	
	- < l"or"e'm.'txt cat | sed "s/ISB/adesille/g" > o'u'tp"ut.t"xt 
		-> ignored
	- echo "" 'bonjour 'c'a' 'va'
		->  bonjour ca va
	- echo ""'bonjour 'c'a' 'va'
		-> bonjour ca va

	- echo sd"gasg$USER'"
		-> sdgasgadesille'
	- echo sd'ggasg$USER'
		-> sdggasg$USER
			=> If (!$arg) == Ignore and "hide"
	- echo bhgvygfvuggubjklhivjgvguvl$USER'exit'
		-> bhgvygfvuggubjklhivjgvguvladesilleexit

	=> ignore every "" or '' except if "''" or '""'
*/

int	open_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == 34)
		{
			while (s[++i] != 34 && s[i])
				;
			if (!s[i])
				return (1);
		}
		if (s[i] == 39)
		{
			while (s[++i] != 39 && s[i])
				;
			if (!s[i])
				return (1);
		}
	}
	return (0);
}

int	close_quotes(char **s)
{
	char	*new_str;
	int		i;

	i = -1;
	new_str = NULL;
	while ((*s)[++i])
	{
		if ((*s)[i] == 34)
		{
			new_str = ft_strjoin(*s, "\"");
			break;
		}
		if ((*s)[i] == 39)
		{
			new_str = ft_strjoin(*s, "'");
			break;
		}
	}
	free(*s);
	*s = new_str;
	return (0);
}

int	array_len(char **tokens)
{
	int i;

	i = -1;
	while (tokens[++i])
		;
	return (i);
}

char	**lexer(char *s)
{
	char	**tokens;
	// char	**new_tokens;
	size_t	i;

	if (!s)
		return (NULL);
	if (is_sh_ope(s, 0, '?'))
		if (add_space(&s, 0))
			return (free(s), NULL);
	if (open_quotes(s))
		if (close_quotes(&s))
			return (free(s), NULL);
	tokens = (char **)malloc((count_rows(s) + 1) * sizeof(char *));
	tokens = splitter(tokens, s, 0);
	if (!tokens)
		return (free(s), NULL);
	i = 0;
	while (tokens[i])
		printf("%s\n", tokens[i++]);
	// if (quotes_manager(tokens))
	// 	return (free(s), free_memory(tokens), NULL);
	// if (is_dollar(tokens, -1, '?', 0))
	// 	if (get_dollar(tokens))
	// 		return (free_memory(tokens), free(s), \
	// 			printf("get_dollar error\n"), NULL);
	return (free(s), tokens);
}
