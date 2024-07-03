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
	if (rl[0] != '\n')
		printf("%s\n", rl);
	add_history(rl);
	append_new_history(rl);
}

int	child(t_ast *ast)
{
	if (close(ast->pipe_fd[0]) == -1)
		return (close(ast->pipe_fd[1]), -1);
	if (ast->fd_in)
		if (dup2(ast->fd_in, STDIN_FILENO) == -1)
			return (-1);
	if (ast->fd_out)
	{
		if (dup2(ast->fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (ast->next)
	{
		if (dup2(ast->pipe_fd[1], STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	warlord_executor(t_ast *ast, char *env[])
{
	pid_t	pid;	

	print_lst(ast);
	printf("\n\n");
	while (ast)
	{
		if (pipe(ast->pipe_fd) == -1)
			return (write(2, strerror(errno), strlen(strerror(errno))), errno);
		pid = fork();
		if (pid == -1)
			return (errno);
		if (pid == 0)
		{
			if (child(ast) == -1)
				return (1);
			if (execve(ast->cmd_path, ast->cmd, env) == -1)
				return (perror("execve"), 1);
		}
		else
		{
			if (close(ast->pipe_fd[1]) == -1)
				return (-1);
			if (dup2(ast->pipe_fd[0], STDIN_FILENO) == -1)
				return (-1);
			if (close(ast->pipe_fd[0]) == -1)
				return (-1);
			if (!ast->next)
				waitpid(pid, NULL, 0);
			ast = ast->next;
		}
	}
	return (0);
}

// TODO : if there's infile in 1st arg don't work

int	main(int argc, char *argv[], char *env[])
{
	t_ast	*ast;
	char	*rl;

	// catchBackslash();
	// catchC();
	(void)argc;
	(void)argv;
	// while (1)
	// {
	rl = NULL;
	ast = NULL;
	if (!prompt(&rl))
	{
		history(rl);
		if (parser(&ast, rl, -1))
			return (mem_manager(0, 0, 0, 'C'), exit(EXIT_FAILURE), 1);
		if (warlord_executor(ast, env))
			return (mem_manager(0, 0, 0, 'C'), exit(EXIT_FAILURE), 1);
	}
	mem_manager(0, 0, 0, 'C');
	// }
}
