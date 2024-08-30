/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:55:21 by adesille          #+#    #+#             */
/*   Updated: 2024/08/29 16:51:11 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! TODO : Add -Werror

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
	// full_prompt = ft_strjoin(ft_strjoin(BLUE, prompt), DEF);
	// s = readline(full_prompt);
	handle_sig_c(0);
	s = readline(prompt);
	handle_sig_c(0);
	if (!s)
	{
		if (isatty(STDIN_FILENO)) // ! to use mpanic
			write(2, "exit\n", 6);
		exit(return_(0, GET));
	}
	if (!ft_strlen(s))
		return (free(s), 1);
	*rl = ft_strdup(s);
	free(s);
	return (0);
}

int	stds_manager(int *stdin_origin, int *stdout_origin, int token)
{
	if (token == DUP_STD)
	{
		*stdin_origin = dup(STDIN_FILENO);
		*stdout_origin = dup(STDOUT_FILENO);
		mem_manager(0, 0, *stdin_origin, SAVE_FD);
		mem_manager(0, 0, *stdout_origin, SAVE_FD);
	}
	else
	{
		dup2(*stdin_origin, STDIN_FILENO);
		dup2(*stdout_origin, STDOUT_FILENO);
	}
	return (0);
}

void	init_utils(char *env[], char *cwd)
{
	get_envv(env, 0, INIT);
	get_cwdd(cwd, 0, INIT);
	free(cwd);
	exportt(env, 0, INIT);
}

int	factory(char *rl)
{
	int		parsing;
	int		stdin_origin;
	int		stdout_origin;
	t_ast	*ast;

	ast = NULL;
	stds_manager(&stdin_origin, &stdout_origin, DUP_STD);
	history(rl);
	parsing = parser(&ast, rl);
	if (parsing == -1)
		return (0);
	else if (parsing)
		return (mem_manager(0, 0, 0, CLEAR_MEMORY), exit(EXIT_FAILURE), 1);
	if (!execute(ast))
		return (mem_manager(0, 0, 0, CLEAR_MEMORY), 1);
	stds_manager(&stdin_origin, &stdout_origin, CLOSE_STD);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*rl;
	int		is_eof;

	(void)argc;
	(void)argv;
	init_utils(env, getcwd(NULL, 0));
	signals_handler();
	while (1)
	{
		rl = NULL;
		is_eof = prompt(&rl);
		if (is_eof == -1)
			break ;
		if (!is_eof)
			if (factory(rl))
				return (return_(0, GET));
	}
	mem_manager(0, 0, 0, CLEAR_MEMORY);
	return (return_(0, GET));
}
