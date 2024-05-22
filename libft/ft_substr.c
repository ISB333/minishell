/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:05:19 by adesille          #+#    #+#             */
/*   Updated: 2023/11/06 16:49:31 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		size;

	if (s == NULL)
		return (NULL);
	size = (ft_strlen(s));
	if (start >= ((unsigned int)size))
		return (ft_strdup(""));
	if (len > size - start)
		len = size - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s[start], len + 1);
	str[len] = '\0';
	return (str);
}
