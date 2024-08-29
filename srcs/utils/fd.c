/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:59:09 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/29 12:54:21 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: closes a file descriptor.
 * 
 * @param fd: the file descriptor to close.
 *
 * ⬅️ Return: int, 0 on success, -1 on failure.
 */
int	close_file_descriptor(const t_fd fd)
{
	return (close(fd) == 0);
}

/**
 * 📋 Description: duplicates a file descriptor to a specified target.
 * 
 * @param fd: the file descriptor to duplicate.
 * @param std: the target file descriptor (e.g., STDIN_FILENO, STDOUT_FILENO).
 *
 * ⬅️ Return: int, 0 on success, -1 on failure.
 */
int	duplicate_fd(const t_fd fd, const int std)
{
	return (dup2(fd, std) != -1);
}

/**
 * 📋 Description: creates a pipe and stores the file descriptors.
 * 
 * @param fd: the array to store the read and write file descriptors.
 *
 * ⬅️ Return: int, 0 on success, -1 on failure.
 */
int	set_pipe(t_pipe_fd *fd)
{
	return (pipe(*fd) == 0);
}
