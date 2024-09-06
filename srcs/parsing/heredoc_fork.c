/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:52:25 by isb3              #+#    #+#             */
/*   Updated: 2024/09/06 13:52:26 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(int pipe_fd[2], char *s, char *del)
{
	int	line_nbr;

	is_in_heredoc(ENTRANCE);
	line_nbr = 1;
	set_signals(TRUE);
	close(pipe_fd[0]);
	mem_manager(0, 0, pipe_fd[1], SAVE_FD);
	while (1)
	{
		s = readline("> ");
		if (!s)
		{
			printf("Warning: here-document at line %d delimited by end-of-file (wanted `%s`)\n", line_nbr, del);
			return (mem_manager(0, 0, 0, CLEAR_MEMORY), (void)exit(0));
		}
		if (!ft_strcmp(s, del))
			return (mem_manager(0, 0, 0, CLEAR_MEMORY), free(s), (void)exit(0));
		write(pipe_fd[1], ft_strjoin(s, "\n"), ft_strlen(s + 1));
		line_nbr++;
		free(s);
	}
	return (close(pipe_fd[1]), mem_manager(0, 0, 0, CLEAR_MEMORY),
		(void)exit(0));
}

int	heredoc_parent(int pipe_fd[2], pid_t pid, t_heredoc *hd)
{
	int		status;
	char	*buffer;

	is_in_heredoc(EXITING);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		printf("\n");
		return (return_(130, ADD), close(pipe_fd[0]), INTERRUPTION);
	}
	else if (WIFEXITED(status))
	{
		buffer = gnhell(pipe_fd[0]);
		while (buffer)
		{
			buffer[ft_strlen(buffer) - 1] = '\0';
			add_node_hd(&hd, buffer);
			buffer = gnhell(pipe_fd[0]);
		}
		return_(0, ADD);
	}
	close(pipe_fd[0]);
	return (get_dollar_hd(hd, 0, 0), 0);
}
