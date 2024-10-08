/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnhell_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:11:08 by adesille          #+#    #+#             */
/*   Updated: 2024/09/01 18:14:00 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_gnl_strlcpy(char *dst, char *src, size_t size)
{
	size_t	src_len;

	if (!src)
		return (0);
	src_len = ft_gnl_strlen(src);
	if (!size)
		return (src_len);
	while (*src && --size)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}

char	*ft_gnl_strdup(char *s)
{
	char	*str;
	int		size;

	if (!s)
		return (NULL);
	size = ft_gnl_strlen(s) + 1;
	str = mem_manager(size, 0, 0, ALLOCATE);
	ft_gnl_strlcpy(str, s, size);
	return (str);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len;

	len = ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1;
	str = mem_manager(len * sizeof(char), 0, 0, ALLOCATE);
	ft_gnl_strlcpy(str, s1, (ft_gnl_strlen(s1) + 1));
	ft_gnl_strlcpy(&str[ft_gnl_strlen(s1)], s2, (ft_gnl_strlen(s2) + 1));
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
