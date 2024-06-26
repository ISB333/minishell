/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:28:31 by isb3              #+#    #+#             */
/*   Updated: 2024/06/26 07:46:40 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *m_malloc(size_t size)
{
    static int i = 0;
    void *ptr;

	// printf("malloc n %d\n", ++i);
	// if (i++ > 300 && i % 2 == 1)
	// 	return (NULL);
    ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

void	quit(char *msg, int return_code)
{
	mem_manager(0, 0, 'C');
	if (msg)
		printf("%s\n", msg);
	exit(return_code);
}

void	*ff(t_memman *mem_list)
{
	t_memman	*temp;

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
	return (NULL);
}

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
		fprintf(stderr, "Memory allocation failed\n");
		quit(NULL, 1);
	}
	new_node = malloc(sizeof(t_memman));
	if (!new_node)
	{
		fprintf(stderr, "Memory manager new node allocation failed\n");
		free(ptr);
		quit(NULL, 1);
	}
	init_node(new_node, mem_list, ptr, token);
	return (ptr);
}

void	*mem_manager(size_t size, int fd, int token)
{
	static t_memman	*mem_list = NULL;
	int				*fd_ptr;

	if (token == 'A')
		return (allocate(&mem_list, size, 'A'));
	if (token == 'O')
	{
		fd_ptr = allocate(&mem_list, size, 'O');
		*fd_ptr = fd;
		return (NULL);
	}
	if (token == 'C')
	{
		ff(mem_list);
		mem_list = NULL;
		return (NULL);
	}
	return (NULL);
}
