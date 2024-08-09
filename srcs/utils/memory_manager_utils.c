/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:57:38 by adesille          #+#    #+#             */
/*   Updated: 2024/08/09 10:46:02 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_init(char *msg, char *file)
{
	char	*s;

	s = ft_strjoin(ft_strjoin("❌ minihell: ", file), ": ");
	s = ft_strjoin(s, msg);
	s = ft_strjoin(RED, s);
	s = ft_strjoin(s, DEF);
	s = ft_strjoin(s, " ❌\n");
	return (s);
}

int	error(char *msg, char *file, int return_code)
{
	if (msg)
	{
		write(2, "minihell: ", ft_strlen("minihell: "));
		if (file)
		{
			write(2, file, ft_strlen(file));
			write(2, ": ", 2);
		}
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	if (return_code)
	{
		return_(return_code, ADD);
		return (return_code);
	}
	return (1);
}

void	close_all_fds(t_memman *mem_list)
{
	while (mem_list)
	{
		if (mem_list->type == FD)
		{
			close(*(int *)mem_list->ptr);
			free(mem_list->ptr);
			mem_list->type = NONE;
			mem_list->ptr = NULL;
		}
		mem_list = mem_list->next;
	}
}

void	ff_lock(t_memman *mem_lock)
{
	t_memman	*temp;

	while (mem_lock)
	{
		temp = mem_lock;
		mem_lock = mem_lock->next;
		if (temp->type == FD)
			close(*(int *)temp->ptr);
		if (temp->ptr)
		{
			free(temp->ptr);
			temp->ptr = NULL;
		}
		free(temp);
	}
}

void	ff(t_memman *mem_list, int i)
{
	char		*path;
	char		*heredoc;
	t_memman	*temp;

	path = ft_strjoin(get_cwdd(0, 0, HOME), "/hd");
	while (++i < 50 && path)
	{
		heredoc = ft_strjoin(path, ft_itoa(i));
		if (!access(heredoc, R_OK))
			unlink(heredoc);
	}
	while (mem_list)
	{
		temp = mem_list;
		mem_list = mem_list->next;
		if (temp->type == FD)
			close(*(int *)temp->ptr);
		if (temp->ptr)
		{
			free(temp->ptr);
			temp->ptr = NULL;
		}
		free(temp);
	}
}
