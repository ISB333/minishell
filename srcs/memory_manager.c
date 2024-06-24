/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:28:31 by isb3              #+#    #+#             */
/*   Updated: 2024/06/24 12:09:34 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// __thread t_memman *mem_list = NULL;

// void *m_malloc(size_t size) 
// {
//     static int i = 0;
//     void *ptr;

// 	if (i++ % 2 == 0)
// 		return(NULL);
//     ptr = malloc(size);
//     if (!ptr) {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }
//     return ptr;
// }

void	*ff(t_memman *mem_list, int token)
{
    t_memman *temp;
	int i = 0;

	while (mem_list)	
	{
	    temp = mem_list;
        mem_list = mem_list->next;
		if (temp->ptr)
		{
			free(temp->ptr);
			temp->ptr = NULL;
		}
        free(temp);
		// printf("list n°%d\n", ++i);
	}
	if (!token)
		exit(EXIT_SUCCESS);
	if (token == 1)
		exit(EXIT_FAILURE);
	return (NULL);
}

void	*allocate(t_memman **mem_list, ptrType type, size_t size)
{
	t_memman *new_node;
	t_memman *last_node;
	void *ptr;
	
	static int i = 0;

	printf("malloc n°%d\n", ++i);
	ptr = malloc(size);
	if (!ptr)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_node = malloc(sizeof(t_memman));
	if (!new_node)
	{
		fprintf(stderr, "Memory allocation for tracking node failed\n");
		free(ptr);
		exit(EXIT_FAILURE);
	}
	new_node->ptr = ptr;
	new_node->type = type;
	new_node->next = NULL;
	if (!*mem_list)
		*mem_list = new_node;
	else
	{
		last_node = *mem_list;
		while(last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	// new_node->size = size;
	return (ptr);
}

void	*printf_lst(t_memman *mem_lst)
{

    t_memman *temp;
	int i = 0;
	int k = 0;

	int j = 0;
	temp = mem_lst;
	while (temp)	
	{
		printf("%d = ", ++j);
		if (temp->type == ARR_ARR)
		{
			i = 0;
			printf("\n\nARR_ARR\n");
			char ***arr = (char ***)temp->ptr;
			while(arr[i])
			{
				k = 0;
				while(arr[i][k])
					printf("%s\n", arr[i][k++]);
				i++;
			}
		}
		else if (temp->type == ARRAY)
		{
			i = 0;
			printf("\n\nARRAY\n");
			char **arr = (char **)temp->ptr;
			while(arr[i])
				printf("%s\n", arr[i++]);
		}
		else if (temp->type == STRING)
			printf("%s\n", (char *)temp->ptr);
        temp = temp->next;
	}
	return(NULL);
}

void	*mem_manager(size_t size, ptrType type, int token)
{
	static t_memman *mem_list = NULL;

	if (token == 'A')
		return (allocate(&mem_list, type, size));
	if (token == 'S')
		return (ff(mem_list, EXIT_SUCCESS));
	if (token == 'F')
		return (ff(mem_list, EXIT_FAILURE));
	if (token == 'C')
		return (ff(mem_list, -1));
	if (token == 'P')
		return (printf_lst(mem_list));
	return (NULL);
}