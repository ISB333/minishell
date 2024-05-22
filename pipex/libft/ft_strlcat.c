/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:54:50 by adesille          #+#    #+#             */
/*   Updated: 2023/11/06 14:19:34 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dstlen;
	unsigned int	srclen;

	if ((dst == NULL || src == NULL) && size == 0)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen((char *)src);
	if (size <= dstlen)
		return (size + srclen);
	ft_strlcpy(&dst[dstlen], src, size - dstlen);
	return (dstlen + srclen);
}
