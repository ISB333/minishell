/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:27:50 by aheitz            #+#    #+#             */
/*   Updated: 2024/08/21 13:50:39 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 📋 Description: finds a node in a linked list (next must be the first field).
 * 
 * @param list: the head of the list to browse.
 * @param n: the index of the node to reach.
 *
 * ⬅️ Return: void *, pointer to the found node, or NULL if not found.
 */
void	*get_node_at(void *list, const int n)
{
	t_linked_list	*current;
	int				remaining;

	if (!list || (n < 0 && n != PENULTIMATE && n != LAST))
		return (NULL);
	remaining = n;
	current = (t_linked_list *)list;
	while (current->next)
	{
		if ((n > 0 && remaining--)
			|| (n == PENULTIMATE && current->next->next)
			|| (n == LAST && current->next))
			current = current->next;
		else
			break ;
	}
	return (current);
}
