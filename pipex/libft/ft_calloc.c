/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:58:27 by adesille          #+#    #+#             */
/*   Updated: 2023/11/06 16:46:33 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		*arr;
	size_t	overflowpro;

	if (!nmemb || !size)
		return (malloc(0));
	overflowpro = size * nmemb;
	if (overflowpro / nmemb != size)
		return (NULL);
	arr = malloc(overflowpro);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, nmemb * size);
	return (arr);
}
