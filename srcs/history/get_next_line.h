/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:13:37 by isb3              #+#    #+#             */
/*   Updated: 2024/06/24 09:36:31 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*gnhell(int fd);
size_t	ft_strlen(const char *str);
size_t	ft_gnl_strlcpy(char *dst, char *src, size_t size);
char	*ft_gnl_strdup(char *s);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

#endif