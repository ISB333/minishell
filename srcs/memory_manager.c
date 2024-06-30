/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:28:31 by isb3              #+#    #+#             */
/*   Updated: 2024/06/30 08:10:11 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	*m_malloc(size_t size)
// {
// 	static int	i = 0;
// 	void		*ptr;

// 	// printf("malloc n %d\n", ++i);
// 	// if (i++ > 300 && i % 2 == 1)
// 	// 	return (NULL);
// 	ptr = malloc(size);
// 	if (!ptr)
// 	{
// 		fprintf(stderr, "Memory allocation failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (ptr);
// }

char	*error_init(char *msg, char *file)
{
	char	*s;

	s = ft_strjoin(ft_strjoin("minihell: ", file), ": ");
	return (ft_strjoin(s, msg));
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
		error_code = return_code;
		printf("error_code = %d\n", error_code);
		return (return_code);
	}
	return (1);
}

void	*ff(t_memman *mem_list)
{
	static char	heredoc[26] = "./srcs/parsing/heredoc/hd0";
	t_memman	*temp;
	int			i;

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
	i = -1;
	while (++i < 50)
	{
		heredoc[25] = i + '0';
		if (!access(heredoc, R_OK))
			unlink(heredoc);
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
		mem_manager(0, 0, 0, 'C');
		exit(EXIT_FAILURE);
	}
	new_node = malloc(sizeof(t_memman));
	if (!new_node)
	{
		fprintf(stderr, "Memory manager new node allocation failed\n");
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
			printf("CLEAR\n");
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
			if (prev)
				prev->next = mem_temp->next;
			else
				*mem_list = mem_temp->next;
			free(mem_temp);
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
	if (token == 'F')
		return (free_ptr(&mem_list, ptr));
	if (token == 'C')
	{
		ff(mem_list);
		mem_list = NULL;
		return (NULL);
	}
	return (NULL);
}
