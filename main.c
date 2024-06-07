/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/05/31 16:44:22 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1. Lexer
		- Split each string
			-> 1st word = cmd (except if < or >)
			-> next = args (except if | or > etc..)
		- Tokenize them
		e.g:
			if ("\n")
				return (NEWLINE);
			if (">")
				return (GREAT).
			if ("<")
				return (LESS).
			if (">>")
				return (GREATGREAT).
			if (">&")
				return (GREATAMPERSAND).
			if ("|")
				return (PIPE).
			if ("&")
				return (AMPERSAND).
		- Wildcards
			- * matches every following characters
			- ? matches one character
			-> wildcards by default don't match hidden files, except if '.' is specified
	2. Parser
		- Arrange these tokens into an Abstract Syntax Tree
		e.g:
			Assignment
			├── Variable: result
			└── Expression: Multiplication
				├── Left: Addition
				│   ├── Left: Identifier (a)
				│   └── Right: Integer Literal (42)
				└── Right: Subtraction
					├── Left: Identifier (b)
					└── Right: Integer Literal (7)
	
	3. Expander
	4. Execute
	5. loop or (exit , shutdown, reboot)
	----------------------------------------------------------------------------
	-- Special cases:
	- cmd1; cmd2; etc..
		-> execute and display each one
		-> loop
		-> conditional structure
		-> grouping
			e.g:
			( ls; pwd; date ) > outputfile 
	- 
*/

int	ft_do_all()
{
	char	*rl;
	char	*prompt;

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
	lexer(rl);
	// parser();
	if (!ft_strcmp(rl, "exit\0"))
		return (free(rl), 0);
	free(rl);
	return (-1);
}

int	main(int argc, char *argv[], char *env[])
{
	int	to_do;

	catchBackslash();
	catchC();
	// rl = NULL;
	if (argc)
	{
		while (1)
		{
			to_do = ft_do_all();
			if (to_do == 0)
				return (write(1, "exit\n", 5), exit(EXIT_SUCCESS), 0);
			if (to_do == 1)
				return (exit(EXIT_FAILURE), 1);
		}
	}
	return (0);
}
