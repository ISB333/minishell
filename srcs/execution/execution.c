/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:57:15 by adesille          #+#    #+#             */
/*   Updated: 2024/08/29 13:53:45 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 🔒 Static function prototypes for internal use -------------------------- 🔒 */

static int	fork_and_execute(t_ast *ast);
static int	execute_child_process(t_ast *ast);
static int	execute_parent_process(t_ast *ast);

/**
 * 📋 Description: main function responsible for executing commands in pipeline.
 * 
 * @param ast: the abstract syntax tree (AST) representing the list of commands.
 *
 * ⬅️ Return: int, SUCCESS if the execution is successful, otherwise FAILURE.
 */
int	execute(t_ast *ast)
{
	t_ast	*cmd;

	if (!ast)
		return (SUCCESS);
	if (!ast->next && is_builtin(ast) && is_builtin(ast) != ECH)
		call_builtins(ast, is_builtin(ast));
	else
	{
		cmd = ast;
		while (cmd)
		{
			if (!fork_and_execute(cmd))
				return (FAILURE);
			cmd = cmd->next;
		}
		wait_for_children(ast);
		display_errors(ast);
	}
	return (SUCCESS);
}

/**
 * 📋 Description: forks a new process and executes the command.
 * 
 * @param ast: the abstract syntax tree (AST) node representing the command.
 *
 * ⬅️ Return: int, SUCCESS if the command is successfully, otherwise FAILURE.
 */
static int	fork_and_execute(t_ast *ast)
{
	if (!set_pipe(&ast->pipe_fd))
		return (write(STDERR_FILENO, strerror(errno), strlen(strerror(errno))),
			FAILURE);
	ast->pid = fork();
	if (ast->pid == INVALID)
		return (FAILURE);
	if (ast->pid == CHILD)
	{
		if (!execute_child_process(ast))
			return (mem_manager(0, NULL, 0, CLEAR_MEMORY), exit(1), 1);
		if (is_builtin(ast))
		{
			call_builtins(ast, is_builtin(ast));
			quit(EXIT_SUCCESS);
		}
		else if (ast->cmd_path)
		{
			mem_manager(0, NULL, 0, KILL_ALL_FD);
			execve(ast->cmd_path, ast->cmd, get_envv(NULL, NULL, GET));
		}
		quit(EXIT_FAILURE);
	}
	else if (execute_parent_process(ast))
		return (SUCCESS);
	return (FAILURE);
}

/**
 * 📋 Description: sets up and executes the command in the child process.
 * 
 * @param ast: the abstract syntax tree (AST) node representing the command.
 *
 * ⬅️ Return: int, SUCCESS if process is set up and executed, otherwise FAILURE.
 */
static int	execute_child_process(t_ast *ast)
{
	if (!close_file_descriptor(ast->pipe_fd[READ]))
		return (close_file_descriptor(ast->pipe_fd[WRITE]), FAILURE);
	if (ast->fd_in && ast->fd_in != INVALID)
	{
		if (!duplicate_fd(ast->fd_in, STDIN_FILENO))
			return (close_file_descriptor(ast->fd_in), FAILURE);
		if (!close_file_descriptor(ast->fd_in))
			return (FAILURE);
	}
	if (ast->fd_out && ast->fd_out != INVALID)
	{
		if (!duplicate_fd(ast->fd_out, STDOUT_FILENO))
			return (close_file_descriptor(ast->fd_out), FAILURE);
		if (!close_file_descriptor(ast->fd_out))
			return (FAILURE);
	}
	else if (ast->next)
	{
		if (!duplicate_fd(ast->pipe_fd[WRITE], STDOUT_FILENO))
			return (close_file_descriptor(ast->pipe_fd[WRITE]), FAILURE);
	}
	if (!close_file_descriptor(ast->pipe_fd[WRITE]))
		return (FAILURE);
	return (SUCCESS);
}

/**
 * 📋 Description: manages parent process to handle pipes and wait for children.
 * 
 * @param ast: the abstract syntax tree (AST) node representing the command.
 *
 * ⬅️ Return: int, SUCCESS if process is managed correctly, otherwise FAILURE.
 */
static int	execute_parent_process(t_ast *ast)
{
	int status;
	int exit_code;

	if (ast->cmd && *ast->cmd && ft_strncmp(*ast->cmd, "./", 2) == EQUAL)
	{
		waitpid(ast->pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (!ast->error_code)
				return_(exit_code, ADD);
			else if (ast->error_code)
				return_(ast->error_code, ADD);
		}
	}
	if (close_file_descriptor(ast->pipe_fd[WRITE])
		&& duplicate_fd(ast->pipe_fd[READ], STDIN_FILENO))
	{
		if (close_file_descriptor(ast->pipe_fd[READ]))
			return (SUCCESS);
	}
	else
		close_file_descriptor(ast->pipe_fd[READ]);
	return (FAILURE);
}
