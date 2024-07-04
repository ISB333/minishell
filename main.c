/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/07/03 15:35:17y isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_error_code = 0;

// ! TODO : Add -Werror

// TODO : modify functions where there's get_env

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
	if (!s || !ft_strlen(s))
		return (free(s), 1);
	*rl = ft_strdup(s);
	free(s);
	return (0);
}

void	history(char *rl)
{
	add_history(rl);
	append_new_history(rl);
}

int	stds_manager(int *stdin_origin, int *stdout_origin, int token)
{
	if (token == DUP_STD)
	{
		*stdin_origin = dup(STDIN_FILENO);
		*stdout_origin = dup(STDOUT_FILENO);
		mem_manager(0, 0, *stdin_origin, 'O');
		mem_manager(0, 0, *stdout_origin, 'O');
	}
	else
	{
		dup2(*stdin_origin, STDIN_FILENO);
		dup2(*stdout_origin, STDOUT_FILENO);
		mem_manager(0, 0, 0, 'C');
	}
	return (0);
}

// ! Heredoc syscall
// ! Heredoc 

int	main(int argc, char *argv[], char *env[])
{
	int		stdin_origin;
	int		stdout_origin;
	t_ast	*ast;
	char	*rl;

	// catchBackslash();
	// catchC();
	(void)argc;
	(void)argv;
	while (1)
	{
		rl = NULL;
		ast = NULL;
		stds_manager(&stdin_origin, &stdout_origin, DUP_STD);
		if (!prompt(&rl))
		{
			history(rl);
			if (parser(&ast, rl, -1))
				return (mem_manager(0, 0, 0, 'C'), exit(EXIT_FAILURE), 1);
			if (warlord_executor(ast, env))
				return (mem_manager(0, 0, 0, 'C'), exit(EXIT_FAILURE), 1);
		}
		stds_manager(&stdin_origin, &stdout_origin, CLOSE_STD);
	}
}
