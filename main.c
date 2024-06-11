/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/06/11 10:04:06 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// * echo: Join arg with a space, it dont give a fuck if there's thousands space between them
// ! if  there's a NEWLINE outside of quotes, command after are not linked to those above, EXCEPTED if there's a pipe at the EOL ! //

int	main()
{
	char	*rl;
	char	*prompt;
	t_ast	*ast;

	add_previous_history();
	int test = open("test.txt", O_RDWR | O_CREAT, 0644);
	// while ((rl = gnhell(test)) != NULL)
	while (1)
	{
		prompt = get_prompt();
		if (!prompt)
			return (printf("prompt error\n"), 1);
		rl = readline(prompt);
		free(prompt);
		if (rl == NULL)
			return (0);
		add_history(rl);
		append_new_history(rl);
		if (!ft_strcmp(rl, "exit\0"))
			return (free(rl), exit(EXIT_SUCCESS), 0);
		if (parser(&ast, lexer(rl)))
			return (1);
	}
	return (1);
}
