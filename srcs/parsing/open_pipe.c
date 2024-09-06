/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:16:50 by isb3              #+#    #+#             */
/*   Updated: 2024/09/06 14:16:53 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_op(t_pipe **op, char *s)
{
	t_pipe	*new_node;
	t_pipe	*last_node;

	new_node = mem_manager(sizeof(t_pipe), 0, 0, ALLOCATE);
	new_node->s = ft_strdup(s);
	new_node->next = NULL;
	if (!*op)
		*op = new_node;
	else
	{
		last_node = *op;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

void	join_op(t_pipe *op, char **s)
{
	int		len;
	t_pipe	*tmp;

	tmp = op;
	while (tmp)
	{
		len += ft_strlen(tmp->s);
		tmp = tmp->next;
	}
	*s = mem_manager(len + 1, 0, 0, ALLOCATE);
	*s = ft_strdup(op->s);
	op = op->next;
	while (op)
	{
		*s = ft_strjoin(*s, op->s);
		op = op->next;
	}
}

void	open_pipe_child(int pipe_fd[2])
{
	char	*s;

	is_in_open_pipe(ENTRANCE);
	close(pipe_fd[0]);
	set_signals(TRUE);
	mem_manager(0, 0, pipe_fd[1], SAVE_FD);
	while (1)
	{
		s = readline("> ");
		if (!s)
		{
			error("syntax error: unexpected end of file", NULL, 2);
			return (mem_manager(0, 0, 0, CLEAR_MEMORY), (void)exit(2));
		}
		write(pipe_fd[1], s, ft_strlen(s));
		if (!is_pipe(s, 0, '?') && ft_strlen(s))
			return (free(s), mem_manager(0, 0, 0, CLEAR_MEMORY), (void)exit(0));
		free(s);
	}
	return (close(pipe_fd[1]), mem_manager(0, 0, 0, CLEAR_MEMORY),
		(void)exit(0));
}

char	*open_pipe_parent(int pipe_fd[2], pid_t pid, t_pipe *op, char **s)
{
	int		status;
	char	*buffer;

	is_in_open_pipe(EXITING);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
		return (close(pipe_fd[0]), exit(2), NULL);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(pipe_fd[0]), printf("\n"), return_(130, ADD), NULL);
	else if (WIFEXITED(status))
	{
		buffer = gnhell(pipe_fd[0]);
		while (buffer)
		{
			buffer[ft_strlen(buffer)] = '\0';
			add_node_op(&op, buffer);
			buffer = gnhell(pipe_fd[0]);
		}
		return_(0, ADD);
	}
	close(pipe_fd[0]);
	return (join_op(op, s), "NICE");
}

int	open_pipe_manager(char **s)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_pipe	*op;

	op = NULL;
	ignore_signals();
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), FAILURE);
	pid = fork();
	if (pid == -1)
		return (perror("pipe"), FAILURE);
	else if (pid == 0)
		open_pipe_child(pipe_fd);
	else if (!open_pipe_parent(pipe_fd, pid, op, s))
		return (FAILURE);
	return (0);
}
