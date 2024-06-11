/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/06/11 12:34:50 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// * echo: Join arg with a space, it dont give a fuck if there's thousands space between them
// ! if  there's a NEWLINE outside of quotes, command after are not linked to those above, EXCEPTED if there's a pipe at the EOL ! //

int	ft_do_all()
{
	t_ast	*ast;
	char	*rl;
	char	*prompt;

	add_previous_history();
	prompt = get_prompt();
	if (!prompt)
		return (printf("prompt error\n"), 1);
	rl = readline(prompt);
	free(prompt);
	if (rl == NULL)
		return (0);
	add_history(rl);
	if (rl[0] != '\n')
		printf("%s\n", rl);
	add_history(rl);
	append_new_history(rl);
	if (!ft_strcmp(rl, "exit\0"))
		return (free(rl), 0);
	if (parser(&ast, lexer(rl)))
		return (1);
	return (-1);
}

int	main()
{
	int	to_do;

	// catchBackslash();
	// catchC();
	// rl = NULL;
	while (1)
	{
		to_do = ft_do_all();
		if (to_do == 0)
			return (write(1, "exit\n", 5), exit(EXIT_SUCCESS), 0);
		if (to_do == 1)
			return (exit(EXIT_FAILURE), 1);
	}
}
