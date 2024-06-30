/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 07:26:59 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_code = 0;

// ! if  there's a NEWLINE outside of quotes, command after are not linked to those above, EXCEPTED if there's a pipe at the EOL ! //
// ! if "echo -nnnnnnnnnnnnnnnnnnnn" || "echo -n-n-n-n-n-n-n-n-n" count as 1 
// ! if exit +100 return code will be 100 (not if multiple +)

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

int	main()
{

	// catchBackslash();
	// catchC();
	while (1)
	{
		t_ast	*ast;
		char	*rl;
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
