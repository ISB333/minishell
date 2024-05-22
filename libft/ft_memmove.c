/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:16:00 by adesille          #+#    #+#             */
/*   Updated: 2023/11/06 14:05:22 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*srcc;
	unsigned char	*destt;

	srcc = (unsigned char *)src;
	destt = (unsigned char *)dest;
	if (src < dest)
	{
		while (n--)
			destt[n] = srcc[n];
		return (dest);
	}
	else if (src > dest)
		ft_memcpy(dest, src, n);
	return (dest);
}
