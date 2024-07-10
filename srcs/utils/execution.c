/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:57:15 by adesille          #+#    #+#             */
/*   Updated: 2024/07/10 10:46:08by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_builtins(t_ast *ast, int c, int token)
{
	int	return_code;

	return_code = 0;
	if (c == CD)
		return_code = cd(ast->cmd);
	if (c == PWD)
		pwdd();
	if (c == ECH)
		echoo(ast->cmd);
	if (c == EXPORT && !ast->cmd[1])
		exportt(0, 0, PRINT);
	if (c == EXPORT && ast->cmd[1])
		exportt(0, ast->cmd[1], ADD);
	if (c == ENV)
		get_envv(0, 0, PRINT);
	if (c == UNSET)
	{
		exportt(0, ast->cmd[1], UNSET);
		get_envv(0, ast->cmd[1], UNSET);
	}
	if (token == EXIT)
		quit(EXIT_SUCCESS);
	return (return_code);
}

int	child(t_ast *ast)
{
	if (close(ast->pipe_fd[0]))
		return (-1);
		// return (close(ast->pipe_fd[1]), -1);
	if (ast->fd_in)
	{
		if (dup2(ast->fd_in, STDIN_FILENO) == -1 || close(ast->fd_in))
			return (-1);
	}
	if (ast->fd_out)
	{
		if (dup2(ast->fd_out, STDOUT_FILENO) == -1 || close(ast->fd_out))
			return (-1);
	}
	else if (ast->next)
	{
		if (dup2(ast->pipe_fd[1], STDOUT_FILENO) == -1)
			return (-1);
	}
	if (close(ast->pipe_fd[1]))
		return (-1);
	return (0);
}

int	executor(t_ast *ast, char *env[])
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
		else
		{
			mem_manager(0, 0, 0, 'K');
			if (execve(ast->cmd_path, ast->cmd, env) == -1)
				return (perror("execve"), 1);
		}
		quit(EXIT_FAILURE);
	}
	else
	{
		if (ast->cmd_path && !ft_strncmp(ast->cmd_path, "./", 2))
			waitpid(ast->pid, NULL, 0);
		if (close(ast->pipe_fd[1]) || dup2(ast->pipe_fd[0], STDIN_FILENO) == -1
			|| close(ast->pipe_fd[0]))
			return (1);
	}
	return (0);
}

void	wait_and_print_error(t_ast *wait, t_ast *error)
{
	while (wait)
	{
		if (wait->pid)
			waitpid(wait->pid, NULL, 0);
		wait = wait->next;
	}
	if (!wait)
	{
		while (error)
		{
			if (error->error)
				printf("%s\n", error->error);
			error = error->next;
		}
	}
}

int	warlord_executor(t_ast *ast, char *env[])
{
	t_ast	*wait;
	t_ast	*error;

	wait = ast;
	error = ast;
	if (!ast->next && is_builtin(ast))
		call_builtins(ast, is_builtin(ast), 0);
	else
	{
		while (ast)
		{
			if (ast->cmd && !ast->error)
				if (executor(ast, env))
					return (1);
			ast = ast->next;
		}
		wait_and_print_error(wait, error);
	}
	return (0);
}
