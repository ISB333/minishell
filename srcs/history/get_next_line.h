/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:13:37 by isb3              #+#    #+#             */
/*   Updated: 2024/09/02 10:23:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "../../headers/minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*gnhell(int fd);
size_t	ft_gnl_strlen(const char *str);
size_t	ft_gnl_strlcpy(char *dst, char *src, size_t size);
char	*ft_gnl_strdup(char *s);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

#endif