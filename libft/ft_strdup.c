/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:51:42 by adesille          #+#    #+#             */
/*   Updated: 2024/06/25 07:19:29 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strdup(const char *s)
{
	char	*str;
	int		size;

	size = ft_strlen(s) + 1;
	str = mem_manager(size, 'A');
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, size);
	return (str);
}
