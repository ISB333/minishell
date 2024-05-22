/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:59:22 by adesille          #+#    #+#             */
/*   Updated: 2023/11/06 16:51:04 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find(const char *big, const char *little, size_t len, int lillen)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (big[i] && len > 0)
	{
		j = 0;
		while (big[i + j] != '\0' && big[i + j] == little[j])
		{
			if (little[j + 1] == '\0')
			{
				if ((size_t)(lillen) > len)
					return (0);
				return ((char *)&big[i]);
			}
			j++;
		}
		i++;
		len--;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	lillen;
	int	i;

	i = 0;
	lillen = ft_strlen(little);
	if ((big == NULL || little == NULL) && len == 0)
		return (0);
	if (lillen == 0)
		return ((char *)&big[i]);
	return (find(big, little, len, lillen));
}
