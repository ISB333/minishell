/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:05:26 by isb3              #+#    #+#             */
/*   Updated: 2024/06/30 07:28:34 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_previous_history(void)
{
	char	*line;
	char	*line_trimmed;
	int		history;

	history = open("./srcs/history/history.txt", O_RDWR | O_CREAT, 0644);
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

	history = open("./srcs/history/history.txt", O_WRONLY | O_APPEND, 0644);
	if (history == -1)
		return (perror("Error opening file"), EXIT_FAILURE);
	ft_putstr_fd(rl, history);
	ft_putstr_fd("\n", history);
	close(history);
	return (0);
}
