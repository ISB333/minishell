/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:58:27 by adesille          #+#    #+#             */
/*   Updated: 2024/08/23 09:31:03 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		*arr;
	size_t	overflowpro;

	if (!nmemb || !size)
		return (mem_manager(0, 0, 0, ALLOCATE));
	overflowpro = size * nmemb;
	if (overflowpro / nmemb != size)
		return (NULL);
	arr = mem_manager(overflowpro, 0, 0, ALLOCATE);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, nmemb * size);
	return (arr);
}
