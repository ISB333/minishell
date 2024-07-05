/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/07/05 13:49:37 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_error_code = 0;

// ! TODO : Add -Werror

// TODO : modify functions where there's get_env
// TODO : Find a way to print the error msg after all the waitpid
// TODO : execute files

int	prompt(char **rl)
{
	char	*prompt;
	char	*s;
	char	*full_prompt;

	s = NULL;
	prompt = NULL;
	add_previous_history();
	prompt = get_prompt();
	if (!prompt)
		return (printf("prompt error\n"), 1);
	full_prompt = ft_strjoin(ft_strjoin(BLUE, prompt), DEF);
	s = readline(full_prompt);
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
	}
	return (0);
}

/*
	adesille@k1r2p12:~/Desktop/minishell/minishell$ ./minishell
	minihell: ./minishell: command not found
*/

int	main(int argc, char *argv[], char *env[])
{
	int			stdin_origin;
	int			stdout_origin;
	t_ast		*ast;
	char		*rl;

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
			exit_check(ast);
			// print_lst(ast);
			// if (warlord_executor(ast, env))
			// 	return (mem_manager(0, 0, 0, 'C'), exit(EXIT_FAILURE), 1);
		}
		stds_manager(&stdin_origin, &stdout_origin, CLOSE_STD);
	}
	mem_manager(0, 0, 0, 'C');
}
