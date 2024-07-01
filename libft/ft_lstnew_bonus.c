/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:00:04 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 07:35:08 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = mem_manager(sizeof(t_list), 0, 0, 'A');
	if (!head)
	{
		return (NULL);
	}
	head->content = content;
	head->next = NULL;
	return (head);
}
