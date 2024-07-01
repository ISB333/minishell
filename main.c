/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/07/01 13:07:56 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_error_code = 0;

int	prompt(char **rl)
{
	char	*prompt;
	char	*s;

	s = NULL;
	prompt = NULL;
	add_previous_history();
	prompt = get_prompt();
	if (!prompt)
		return (printf("prompt error\n"), 1);
	s = readline(prompt);
	if (!ft_strlen(s))
		return (free(s), 1);
	*rl = ft_strdup(s);
	free(s);
	return (0);
}

void	history(char *rl)
{
	add_history(rl);
	if (rl[0] != '\n')
		printf("%s\n", rl);
	add_history(rl);
	append_new_history(rl);
}

int	main(void)
{
	t_ast	*ast;
	char	*rl;

	// catchBackslash();
	// catchC();
	while (1)
	{
		rl = NULL;
		ast = NULL;
		if (!prompt(&rl))
		{
			history(rl);
			parser(&ast, rl);
		}
		mem_manager(0, 0, 0, 'C');
	}
}
