/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:28:31 by isb3              #+#    #+#             */
/*   Updated: 2024/07/16 08:15:15 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_node(t_memman *new_node, t_memman **mem_list, void *ptr, int token)
{
	t_memman	*last_node;

	new_node->ptr = ptr;
	if (token == 'O')
		new_node->type = FD;
	else
		new_node->type = NONE;
	new_node->next = NULL;
	if (!*mem_list)
		*mem_list = new_node;
	else
	{
		last_node = *mem_list;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

void	*allocate(t_memman **mem_list, size_t size, int token)
{
	t_memman	*new_node;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		mem_manager(0, 0, 0, 'C');
		exit(EXIT_FAILURE);
	}
	new_node = malloc(sizeof(t_memman));
	if (!new_node)
	{
		free(ptr);
		mem_manager(0, 0, 0, 'C');
		exit(EXIT_FAILURE);
	}
	init_node(new_node, mem_list, ptr, token);
	return (ptr);
}

void	close_fd(t_memman *mem_list, int fd)
{
	t_memman	*mem_temp;
	t_memman	*prev;

	mem_temp = mem_list;
	prev = NULL;
	while (mem_temp)
	{
		if (*(int *)mem_temp->ptr == fd)
		{
			close(*(int *)mem_temp->ptr);
			free(mem_temp->ptr);
			if (prev)
				prev->next = mem_temp->next;
			else
				mem_list = mem_temp->next;
			free(mem_temp);
			break ;
		}
		prev = mem_temp;
		mem_temp = mem_temp->next;
	}
}

void	*free_ptr(t_memman **mem_list, void *ptr)
{
	t_memman	*mem_temp;
	t_memman	*prev;

	mem_temp = *mem_list;
	prev = NULL;
	while (mem_temp)
	{
		if (mem_temp->ptr == ptr)
		{
			free(mem_temp->ptr);
			ptr = NULL;
			if (prev)
				prev->next = mem_temp->next;
			else
				*mem_list = mem_temp->next;
			free(mem_temp);
			mem_temp = NULL;
			break ;
		}
		prev = mem_temp;
		mem_temp = mem_temp->next;
	}
	return (NULL);
}

void	*mem_manager(size_t size, void *ptr, int fd, int token)
{
	static t_memman	*mem_list = NULL;
	int				*fd_ptr;

	if (token == 'A')
		return (allocate(&mem_list, size, 'A'));
	if (token == 'O')
	{
		fd_ptr = allocate(&mem_list, sizeof(int), 'O');
		*fd_ptr = fd;
		return (NULL);
	}
	if (token == 'N')
		close_fd(mem_list, fd);
	if (token == 'K')
		close_all_fds(mem_list);
	if (token == 'F')
		return (free_ptr(&mem_list, ptr));
	if (token == 'C')
	{
		ff(mem_list, -1);
		mem_list = NULL;
		return (NULL);
	}
	return (NULL);
}
