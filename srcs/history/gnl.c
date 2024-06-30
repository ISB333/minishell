/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:12:09 by adesille          #+#    #+#             */
/*   Updated: 2024/06/30 07:28:01 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*strchr_n_split(char *stock_buff)
{
	char	*line;
	int		i;

	i = 0;
	while (stock_buff[i] != '\0' && stock_buff[i++] != '\n')
		;
	if (stock_buff[i] == '\0')
		return (ft_gnl_strdup(stock_buff));
	line = mem_manager(i + 1, 0, 0, 'A');
	i = 0;
	while (stock_buff[i] != '\n' && stock_buff[i] != '\0')
	{
		line[i] = stock_buff[i];
		i++;
		if (stock_buff[i] == '\n')
			line[i] = stock_buff[i];
	}
	if (stock_buff[i] == '\n')
		line[i] = stock_buff[i];
	line[++i] = '\0';
	return (line);
}

static char	*get_line(int fd, char *stock_buff, char *read_buff)
{
	int	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(read_buff, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, read_buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		read_buff[bytes_read] = '\0';
		if (bytes_read)
			stock_buff = ft_gnl_strjoin(stock_buff, read_buff);
		if (!ft_strlen(stock_buff))
			return (NULL);
	}
	return (stock_buff);
}

char	*gnhell(int fd)
{
	static char	*stock_buff;
	char		*read_buff;
	char		*line;
	int			linelen;
	int			i;

	if (fd < 0)
		return (NULL);
	i = 0;
	read_buff = mem_manager(100, 0, 0, 'A');
	read_buff[0] = '\0';
	stock_buff = get_line(fd, stock_buff, read_buff);
	if (!stock_buff)
		return (NULL);
	line = strchr_n_split(stock_buff);
	linelen = ft_strlen(line);
	while (stock_buff[linelen])
		stock_buff[i++] = stock_buff[linelen++];
	stock_buff[i] = '\0';
	return (line);
}
