/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:28:31 by isb3              #+#    #+#             */
/*   Updated: 2024/06/21 09:14:02 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// __thread t_memman *mem_list = NULL;


// void	*allocate(t_memman *mem_list, ptrType type, size_t size)
// {
// 	t_memman *new_node;
// 	void *ptr;
	
// 	ptr = m_malloc(size);
// 	if (!ptr)
// 	{
// 		fprintf(stderr, "Memory allocation failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	new_node = m_malloc(sizeof(t_memman));
// 	if (!new_node)
// 	{
// 		fprintf(stderr, "Memory allocation for tracking node failed\n");
// 		free(ptr);
// 		exit(EXIT_FAILURE);
// 	}
// 	new_node->ptr = ptr;
// 	new_node->type = type;
// 	new_node->next = mem_list;
// 	mem_list = new_node;
// 	return (ptr);
// }

// void	free_array_of_array(void *ptr)
// {
// 	char ***arr;
// 	int	i;

// 	i = -1;
// 	arr = (char ***)ptr;
// 	while (arr[++i])
// 		free_memory(arr[i]);
// 	free(arr);
// }

// void	free_array(void *ptr)
// {
// 	char **arr;

// 	arr = (char **)ptr;
// 	free_memory(arr);
// }

// void	*ff(int token)
// {
// 	static t_memman *mem_list = NULL;
//     t_memman *temp;
// 	int i = 0;

// 	while (mem_list)	
// 	{
// 	    temp = mem_list;
//         mem_list = mem_list->next;

// 		if (temp->type == ARR_ARR)
// 			free_array_of_array(temp->ptr);	
// 		else if (temp->type == ARRAY)
// 			free_array(temp->ptr);
// 		else if (temp->type == STRING)
// 			free(temp->ptr);
//         free(temp);
// 		printf("list n°%d\n", ++i);
// 	}
// 	if (!token)
// 		exit(EXIT_SUCCESS);
// 	if (token)
// 		exit(EXIT_FAILURE);
// 	return (NULL);
// }

void *m_malloc(size_t size) 
{
    static int i = 0;
    void *ptr;

	printf("malloc n°%d\n", i++);
	if (i >= 25)
		return(NULL);
    ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}



// void	*mem_manager(size_t size, ptrType type, int token)
// {
// 	static t_memman *mem_list = NULL;

// 	if (token == 'A')
// 		return (allocate(mem_list, type, size));
// 	// if (token == 'S')
// 	// 	return (ff(mem_list, EXIT_SUCCESS));
// 	// if (token == 'F')
// 	// 	return (ff(mem_list, EXIT_FAILURE));
// 	return (NULL);
// }