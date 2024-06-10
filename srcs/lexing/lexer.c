/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/10 14:35:01 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	- cmd {args}
	- redir cmd {args}
	- cmd {args} (redir || pipe)

	===============================================
	if (quotes)
		go_to_closing_quotes();
			join();


	==>
		split_quotes_n_join();
		e.g:
			'ec'"'h'o' b"l'a'bl"a" test
			==
				ec'h'o' blabla (first arg)

		while(s)
			if(quotes)
				rows++;
				forward_to_closing_quotes();
			if(del)
				rows++;
				while(del) --->>>> if multiple del == 1space
				forward


	==> if newline outside quotes
		what is after is considered a command
*/

// int	open_quotes(char *s)
// {
// 	int	i;
// 	int	s_quote;
// 	int	d_quote;

// 	i = 0;
// 	s_quote = 0;
// 	d_quote = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == 34 && (i == 0 || s[i - 1] != '\\'))
// 			d_quote = !d_quote;
// 		else if (s[i] == 39 && (i == 0 || s[i - 1] != '\\'))
// 			s_quote = !s_quote;
// 		i++;
// 	}
// 	if (s_quote || d_quote)
// 		return (1);
// 	return (0);
// }

// int	close_quotes(char **s)
// {
// 	char	*new_str;
// 	int		i;

// 	i = -1;
// 	new_str = NULL;
// 	while ((*s)[++i])
// 	{
// 		if ((*s)[i] == 34)
// 		{
// 			new_str = ft_strjoin(*s, "\"");
// 			break ;
// 		}
// 		if ((*s)[i] == 39)
// 		{
// 			new_str = ft_strjoin(*s, "'");
// 			break ;
// 		}
// 	}
// 	free(*s);
// 	*s = new_str;
// 	return (0);
// }

int	open_quotes(char *s)
{
	int	i;
	int k;
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
	char	**tokens = NULL;
	size_t	i;

	if (!s)
		return (NULL);
	if (is_sh_ope(s, 0, '?'))
		if (add_space(&s, 0, 0, 0))
			return (free(s), NULL);
	printf("%s\n", s);
	if (open_quotes(s))
		return (free(s), printf("Brother, I will smash ur face. Close me dat quote!\n"),
			NULL);
	tokens = (char **)malloc((count_rows(s) + 1) * sizeof(char *));
	tokens = splitter(tokens, s);
	if (!tokens)
		return (free(s), NULL);
	i = -1;
	while (tokens[++i])
		printf("%s\n", tokens[i]);
	return (free(s), tokens);
}
