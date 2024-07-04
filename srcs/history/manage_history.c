/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:05:26 by isb3              #+#    #+#             */
/*   Updated: 2024/07/04 09:44:16 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_previous_history(void)
{
	char	*line;
	char	*line_trimmed;
	int		history;

	history = open("/home/adesille/Desktop/minishell/minishell/srcs/history/history.txt", O_RDWR | O_CREAT, 0777);
	if (history == -1)
		return (perror("Error opening file"), EXIT_FAILURE);
	mem_manager(sizeof(int), 0, history, 'O');
	while (1)
	{
		line = gnhell(history);
		if (!line)
			return (0);
		line_trimmed = ft_strtrim(line, "\n");
		add_history(line_trimmed);
	}
	return (0);
}

int	append_new_history(char *rl)
{
	int	history;

	history = open("/home/adesille/Desktop/minishell/minishell/srcs/history/history.txt", O_WRONLY | O_APPEND, 0777);
	if (history == -1)
		return (perror("Error opening file"), EXIT_FAILURE);
	ft_putstr_fd(rl, history);
	ft_putstr_fd("\n", history);
	close(history);
	return (0);
}
