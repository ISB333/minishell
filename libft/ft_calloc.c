/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:58:27 by adesille          #+#    #+#             */
/*   Updated: 2024/06/21 08:27:59 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		*arr;
	size_t	overflowpro;

	if (!nmemb || !size)
		return (m_malloc(0));
	overflowpro = size * nmemb;
	if (overflowpro / nmemb != size)
		return (NULL);
	arr = m_malloc(overflowpro);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, nmemb * size);
	return (arr);
}
