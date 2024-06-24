/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/06/24 10:19:48 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! if  there's a NEWLINE outside of quotes, command after are not linked to those above, EXCEPTED if there's a pipe at the EOL ! //
// ! if "echo -nnnnnnnnnnnnnnnnnnnn" || "echo -n-n-n-n-n-n-n-n-n" count as 1 
// ! if exit +100 return code will be 100 (not if multiple +)

int	prompt(char **rl)
{
	char	*prompt;

	add_previous_history();
	prompt = get_prompt();
	if (!prompt)
		return (printf("prompt error\n"), 1);
	// printf("\033[0;34m");
	*rl = readline(prompt);
	if (*rl == NULL)
	// printf("\033[0;37m");
		return (1);
	// free(prompt);
	return (0);
}

void	history(char *rl)
{
	// add_history(rl);
	if (rl[0] != '\n')
		printf("%s\n", rl);
	// add_history(rl);
	// append_new_history(rl);
}

int	main()
{
	t_ast	*ast;
	char	*rl;

	// catchBackslash();
	// catchC();
	// rl = NULL;
	// while (1)
	// {
	static int i = 0;
	// while(i++ < 250)
	// {
		int fd = open("test.txt", O_RDONLY);
		ast = NULL;
		rl = gnhell(fd);
		// if (prompt(&rl))
		// 	return (1);
		// history(rl);
		if (!ft_strcmp(rl, "exit\0"))
			return (free(rl), 0);
		parser(&ast, lexer(rl));
		close(fd);
	// }
}
