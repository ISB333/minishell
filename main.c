/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/06/09 07:08:38 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1. Lexer
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
	
	3. Execute
	4. loop or (exit , shutdown, reboot)

	----------------------------------------------------------------------------
	-- Special cases:
		- grouping
		- e'ch'o
		- 'open quote (no need to manage this) 
		- <infile
		- 
*/

int	main()
{
	char	*rl;
	char	*prompt;
	t_ast	*ast;

	add_previous_history();
	int test = open("test.txt", O_RDWR | O_CREAT, 0644);
	while ((rl = gnhell(test)) != NULL)
	{
		prompt = get_prompt();
		if (!prompt)
			return (printf("prompt error\n"), 1);
		// rl = readline(prompt);
		free(prompt);
		if (rl == NULL)
			return (0);
		add_history(rl);
		append_new_history(rl);
		if (!ft_strcmp(rl, "exit\0"))
			return (free(rl), exit(EXIT_SUCCESS), 0);
		if (parser(&ast, lexer(rl)))
			return (free(rl), 1);
	}
	return (1);
}
