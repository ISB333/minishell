/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:58:27 by adesille          #+#    #+#             */
/*   Updated: 2024/06/25 07:18:54 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		*arr;
	size_t	overflowpro;

	if (!nmemb || !size)
		return (mem_manager(0, 'A'));
	overflowpro = size * nmemb;
	if (overflowpro / nmemb != size)
		return (NULL);
	arr = mem_manager(overflowpro, 'A');
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, nmemb * size);
	return (arr);
}
