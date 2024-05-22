/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:23:30 by isb3              #+#    #+#             */
/*   Updated: 2024/05/14 10:01:52 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

int	child(t_data *d)
{
	if (close(d->pipe_fd[0]))
		return (close(d->pipe_fd[1]), -1);
	if (d->it == 0)
		if (dup2(d->infile, STDIN_FILENO) == -1)
			return (-1);
	if (d->it == d->count - 1)
	{
		if (dup2(d->outfile, STDOUT_FILENO) == -1)
			return (-1);
	}
	else
		if (dup2(d->pipe_fd[1], STDOUT_FILENO) == -1)
			return (-1);
	return (0);
}

int	warlord_executor(t_data *d, char *env[])
{
	pid_t	pid;

	if (pipe(d->pipe_fd) == -1)
		return (write(2, strerror(errno), ft_strlen(strerror(errno))), errno);
	pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0)
	{
		if (child(d) == -1)
			return (ff(d, 0, NULL), errno);
		if (execve(d->cmd_paths[d->it], d->args[d->it], env))
			return (close(d->pipe_fd[1]), perror("execve"), 1);
	}
	else if (pid > 0)
	{
		if (d->it == d->count - 2)
			waitpid(pid, NULL, 0);
		if (close(d->pipe_fd[1]), dup2(d->pipe_fd[0], STDIN_FILENO) == -1
			|| close(d->pipe_fd[0]))
			return (-1);
		if (d->it++ < d->count - 1)
			warlord_executor(d, env);
	}
	return (0);
}

// LIBFT MAKEFILE DON'T COMPILE ANYMORE BONUS

int	main(int argc, char *argv[], char *env[])
{
	t_data	*d;

	if (argc <= 4)
		return (printf("argc ERROR\n"), 1);
	else
	{
		if (format_check(argv))
			return (perror("wrong format"), 1);
		d = malloc(sizeof(t_data));
		if (!d)
			return (ft_putstr_fd("malloc\n", 1), 1);
		if (initializer(d, argv, env))
			return (errno);
		if (warlord_executor(d, env))
			return (ff(d, errno, NULL), errno);
		return (ff(d, 0, NULL), 0);
	}
	return (0);
}
