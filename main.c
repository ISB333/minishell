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
	// if (rl[0] != '\n')
		// printf("%s\n", rl);
	add_history(rl);
	append_new_history(rl);
}

int	call_builtins(t_ast *ast, int c)
{
	if (c == CD)
		return (ft_cd(ast));
	if (c == PWD)
		return (ft_pwd());
	if (c == ECH)
		return (ft_echo(ast));
	return (0);
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
	close(ast->pipe_fd[1]);
	return (0);
}

int	warlord_executor(t_ast *ast, char *env[])
{
	while (ast)
	{
		if (ast->error)
		{
			printf("%s\n", ast->error);
			ast = ast->next;
		}
		else if (is_builtin(ast) == CD)
		{
			call_builtins(ast, is_builtin(ast));
			ast = ast->next;
		}
		else
		{
			if (pipe(ast->pipe_fd) == -1)
				return (write(2, strerror(errno), strlen(strerror(errno))), errno);
			ast->pid = fork();
			if (ast->pid == -1)
				return (errno);
			if (ast->pid == 0)
			{
				if (child(ast) == -1)
					return (1);
				if (is_builtin(ast))
					call_builtins(ast, is_builtin(ast));
				else if (execve(ast->cmd_path, ast->cmd, env) == -1)
						return (perror("execve"), 1);
				mem_manager(0, 0, 0, 'C');
				exit(EXIT_SUCCESS);
			}
			else
			{
				if (close(ast->pipe_fd[1]) == -1)
					return (-1);
				if (dup2(ast->pipe_fd[0], STDIN_FILENO) == -1)
					return (-1);
				if (close(ast->pipe_fd[0]) == -1)
					return (-1);
				ast = ast->next;
			}
		}
	}
	return (0);
}

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
		stdin_origin = dup(STDIN_FILENO);
		stdout_origin = dup(STDOUT_FILENO);
		mem_manager(0, 0, stdin_origin, 'O');
		mem_manager(0, 0, stdout_origin, 'O');
		if (!prompt(&rl))
		{
			history(rl);
			if (parser(&ast, rl, -1))
				return (mem_manager(0, 0, 0, 'C'), exit(EXIT_FAILURE), 1);
			if (warlord_executor(ast, env))
				return (mem_manager(0, 0, 0, 'C'), exit(EXIT_FAILURE), 1);
			while (ast->next)
			{
				waitpid(ast->pid, NULL, 0);
				ast = ast->next;
			}
		}
		dup2(stdin_origin, STDIN_FILENO);
		dup2(stdout_origin, STDOUT_FILENO);
		mem_manager(0, 0, 0, 'C');
	}
}
