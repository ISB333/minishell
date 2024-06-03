/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:35 by adesille          #+#    #+#             */
/*   Updated: 2024/06/03 09:33:48 by isb3             ###   ########.fr       */
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

void	free_memory(char **array)
{
	int	j;

	j = 0;
	if (!array)
		return ;
	while (array[j])
		j++;
	while (j-- > 0)
		free(array[j]);
	free(array);
}

char	**lexer(char *s)
{
	char	**tokens;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (is_sh_ope(s, 0, '?') || is_quotes(s, 0, '?'))
		if (add_space(&s, 0, 0))
			return (NULL);
	tokens = (char **)malloc((count_rows(s) + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens = splitter(tokens, s, i);
	if (is_dollar(tokens, -1, '?'))
		if (get_dollar(tokens))
			return (NULL);
	while (tokens[i])
		printf("%s\n", tokens[i++]);
	free_memory(tokens);
	return (free(s), NULL);
}
