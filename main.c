/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/05/23 13:38:41 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1. Lexer
		- Split each string
		- Tokenize them
			== e.g: result = (a + 42) * (b - 7)
			    result (identifier)
				= (operator)
				( (left parenthesis)
				a (identifier)
				+ (operator)
				42 (integer literal)
				) (right parenthesis)
				* (operator)
				( (left parenthesis)
				b (identifier)
				- (operator)
				7 (integer literal)
				) (right parenthesis)
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
	
	3. Error_management
	4. Execute
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
			printf("%s\n", rl);
			// lexer();
			// parser();
			free(prompt);
			if (!ft_strcmp(rl, "exit\0"))
				return (free(rl), exit(EXIT_SUCCESS), 0);
			free(rl);
		}
	}
	return (1);
}
