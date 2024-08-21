/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:57:15 by adesille          #+#    #+#             */
/*   Updated: 2024/08/21 10:04:05 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child(t_ast *ast)
{
	if (close(ast->pipe_fd[0]))
		return (close(ast->pipe_fd[1]), -1);
	if (ast->fd_in && ast->fd_in != -1)
	{
		if (dup2(ast->fd_in, STDIN_FILENO) == -1)
			return (close(ast->fd_in), -1);
		if (close(ast->fd_in))
			return (1);
	}
	if (ast->fd_out && ast->fd_out != -1)
	{
		if (dup2(ast->fd_out, STDOUT_FILENO) == -1)
			return (close(ast->fd_out), -1);
		if (close(ast->fd_out))
			return (-1);
	}
	else if (ast->next)
	{
		if (dup2(ast->pipe_fd[1], STDOUT_FILENO) == -1)
			return (close(ast->pipe_fd[1]), -1);
	}
	if (close(ast->pipe_fd[1]))
		return (-1);
	return (0);
}

int	parent(t_ast *ast)
{
	if (ast->cmd && ast->cmd[0] && !ft_strncmp(ast->cmd[0], "./", 2))
		waitpid(ast->pid, NULL, 0);
	if (close(ast->pipe_fd[1]))
		return (close(ast->pipe_fd[0]), 1);
	if (dup2(ast->pipe_fd[0], STDIN_FILENO) == -1)
		return (close(ast->pipe_fd[0]), 1);
	if (close(ast->pipe_fd[0]))
		return (1);
	return (0);
}

int	executor(t_ast *ast)
{
	if (pipe(ast->pipe_fd) == -1)
		return (write(2, strerror(errno), strlen(strerror(errno))), errno);
	ast->pid = fork();
	if (ast->pid == -1)
		return (errno);
	if (ast->pid == 0)
	{
		if (child(ast) == -1)
			return (mem_manager(0, 0, 0, 'C'), exit(1), 1);
		if (is_builtin(ast))
			call_builtins(ast, is_builtin(ast), EXIT);
		else if (ast->cmd_path)
		{
			mem_manager(0, 0, 0, 'K');
			execve(ast->cmd_path, ast->cmd, get_envv(0, 0, GET));
		}
		quit(EXIT_FAILURE);
	}
	else
		if (parent(ast))
			return (1);
	return (0);
}

void	wait_and_print_error(t_ast *wait, t_ast *error, int exit_status)
{
	int	status;

	while (wait)
	{
		if (wait->cmd && wait->cmd[0] && ft_strncmp(wait->cmd[0], "./", 2))
		{
			exit_status = 0;
			waitpid(wait->pid, &status, 0);
			if (WIFEXITED(status))
			{
				exit_status = WEXITSTATUS(status);
				if (!wait->next && !wait->error_code)
					return_(exit_status, ADD);
				else if (!wait->next && wait->error_code)
					return_(wait->error_code, ADD);
			}
		}
		wait = wait->next;
	}
	while (error)
	{
		if (error->error)
			write(2, error->error, ft_strlen(error->error));
		error = error->next;
	}
}

int	warlord_executor(t_ast *ast)
{
	t_ast	*wait;
	t_ast	*error;

	if (!ast)
		return (0);
	wait = ast;
	error = ast;
	if (!ast->next && is_builtin(ast) && is_builtin(ast) != ECH)
		call_builtins(ast, is_builtin(ast), 0);
	else
	{
		while (ast)
		{
			if (executor(ast))
				return (1);
			ast = ast->next;
		}
		wait_and_print_error(wait, error, 0);
	}
	return (0);
}
