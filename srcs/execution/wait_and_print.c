/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:29:29 by aheitz            #+#    #+#             */
/*   Updated: 2024/09/29 09:11:20 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: waits for each child process to complete its execution.
 *
 * @param cmd: pointer to the list of commands.
 *
 * ⬅️ Return: nothing.
 */
void	wait_for_children(t_ast *cmd)
{
	int	exit_code;
	int	status;

	status = 0;
	while (cmd)
	{
		if (cmd->cmd && *cmd->cmd && ft_strncmp(*cmd->cmd, "./", 2) != EQUAL)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
				if (!cmd->next)
				{
					if (!cmd->error_code)
						return_(exit_code, ADD);
					else if (cmd->error_code)
						return_(cmd->error_code, ADD);
				}
			}
		}
		cmd = cmd->next;
	}
}

/**
 * 📋 Description: prints all errors encountered during command execution.
 *
 * @param cmd: pointer to the list of commands.
 *
 * ⬅️ Return: nothing.
 */
void	display_errors(t_ast *cmd)
{
	while (cmd)
	{
		if (cmd->error)
			write(STDERR_FILENO, cmd->error, ft_strlen(cmd->error));
		cmd = cmd->next;
	}
}
