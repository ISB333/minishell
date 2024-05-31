/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/05/31 13:30:52 by adesille         ###   ########.fr       */
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
		ls -l /home/user
			Command
				├── Name: ls
				└── Arguments:
					├── -l
					└── /home/user

		ls -l | grep 'myfile'
			Pipeline
			├── Command
			│   ├── Name: ls
			│   └── Arguments:
			│       └── -l
			└── Command
				├── Name: grep
				└── Arguments:
					└── 'myfile'

		echo "Hello, World!" > output.txt
			Command
			├── Name: echo
			├── Arguments:
			│   └── "Hello, World!"
			└── Redirection
				├── Type: >
				└── Target: output.txt
		
		ls -l | grep 'myfile' | sort -r > sorted_files.txt
			Pipeline
				├── Command
				│   ├── Name: ls
				│   └── Arguments:
				│       └── -l
				├── Command
				│   ├── Name: grep
				│   └── Arguments:
				│       └── 'myfile'
				└── Command
					├── Name: sort
					├── Arguments:
					│   └── -r
					└── Redirection
						├── Type: >
						└── Target: sorted_files.txt
	
	3. Expander
	4. Execute
	5. loop or (exit , shutdown, reboot)
	----------------------------------------------------------------------------
	-- Special cases:
		- grouping
			e.g:
			( ls; pwd; date ) > outputfile 
		- e'ch'o
		- 'open quote (no need to manage this) 
		- <infile
		- 
*/

int	main(int argc, char *argv[], char *env[])
{
	char	*rl;
	char	*prompt;

	rl = NULL;
	if (argc)
	{
		while (1)
		{
			prompt = get_prompt(env);
			if (!prompt)
				return (printf("prompt error\n"), 1);
			rl = readline(prompt);
			add_history(rl);
			lexer(rl);
			// parser();
			free(prompt);
			if (!ft_strcmp(rl, "exit\0"))
				return (free(rl), exit(EXIT_SUCCESS), 0);
		}
	}
	return (1);
}
