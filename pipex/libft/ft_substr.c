/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:05:19 by adesille          #+#    #+#             */
/*   Updated: 2024/03/16 09:46:36 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
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
