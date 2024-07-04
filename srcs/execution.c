/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:57:15 by adesille          #+#    #+#             */
/*   Updated: 2024/07/04 10:19:46 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_ast	*wait;

	wait = ast;
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
	while (wait->next)
	{
		waitpid(wait->pid, NULL, 0);
		wait = wait->next;
	}
	return (0);
}
