/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:23:18 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 07:35:25 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = mem_manager(len * sizeof(char), 0, 0, 'A');
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, (ft_strlen(s1) + 1));
	ft_strlcpy(&str[ft_strlen(s1)], s2, (ft_strlen(s2) + 1));
	return (str);
}
