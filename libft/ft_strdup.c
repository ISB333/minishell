/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:51:42 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 07:35:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strdup(const char *s)
{
	char	*str;
	int		size;

	size = ft_strlen(s) + 1;
	str = mem_manager(size, 0, 0, 'A');
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, size);
	return (str);
}
