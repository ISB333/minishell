/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:57:28 by adesille          #+#    #+#             */
/*   Updated: 2023/11/06 16:47:48 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destcpy;
	char	*srccpy;

	destcpy = (char *)dest;
	srccpy = (char *)src;
	if (destcpy == NULL && srccpy == NULL)
		return (NULL);
	while (n > 0)
	{
		*destcpy++ = *srccpy++;
		n--;
	}
	return (dest);
}
