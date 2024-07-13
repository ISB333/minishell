/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:05:26 by isb3              #+#    #+#             */
/*   Updated: 2024/07/13 06:11:07 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	history(char *rl)
{
	add_history(rl);
	append_new_history(rl);
}

int	add_previous_history(void)
{
	char	*line;
	char	*line_trimmed;
	int		history;
	char	*path;

	path = ft_strjoin(get_envv(0, "HOME", FIND), "/history.txt");
	history = open(path, O_RDWR | O_CREAT, 0644);
	if (history == -1)
		return (perror("Error opening file"), EXIT_FAILURE);
	mem_manager(0, 0, history, 'O');
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
	int		history;
	char	*path;

	path = ft_strjoin(get_envv(0, "HOME", FIND), "/history.txt");
	history = open(path, O_WRONLY | O_APPEND, 0644);
	if (history == -1)
		return (perror("Error opening file"), EXIT_FAILURE);
	mem_manager(0, 0, history, 'O');
	ft_putstr_fd(rl, history);
	ft_putstr_fd("\n", history);
	return (0);
}
