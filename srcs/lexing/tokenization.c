/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:51 by adesille          #+#    #+#             */
/*   Updated: 2024/05/31 13:39:35 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	-- IGNORE:
	1- "" && ''
		- echo 'Hello, $USER'         # Outputs: Hello, $USER
		- echo "Backslash: \n"       # Outputs: Backslash: \n

	2- 
		- echo "Hello, $USER"        # Outputs: Hello, John
		- echo "Today is $(date)"    # Outputs: Today is [current date]
		- echo 'It\'s a nice day'  # Incorrect: Causes error
		- echo 'It'\''s a nice day'  # Correct: Outputs: It's a nice day

*/


int	is_quotes(char c)
{
	if (c == 39 || c == 34)
		return (1);
	return (0);
}

char	*handle_quotes(char *s)
{
	char	*str;
	int		i;
	int		bad;

	i = -1;
	bad = 0;
	while (s[++i])
		if (is_quotes(s[i]))
			// find_last_q();
			bad++;
	str = malloc(i - bad + 1);
	if (!s)
		return (NULL);
	str[i - bad] = '\0';
	i = 0;
	bad = 0;
	while (s[i])
	{
		if (is_quotes(s[i]))
			i++;
		str[bad++] = s[i++];
	}
	return (free(s), str);
}

char	**tokenizer(char *s)
{
	char **array = NULL;
	size_t i;

	i = 0;
	if (!s)
		return (NULL);
	if (is_sh_ope(s, 0))
		if (add_space(&s, 0, 0))
			return (NULL);
	// str = handle_quotes(str);
	printf("%s\n", s);
	// if (!str)
	// 	return (NULL);
	array = (char **)malloc((count_rows(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = splitter(array, s, i);
	return (array);
}
