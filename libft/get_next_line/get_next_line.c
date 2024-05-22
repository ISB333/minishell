/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:12:09 by adesille          #+#    #+#             */
/*   Updated: 2023/11/30 11:21:30 by adesille         ###   ########.fr       */
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
		return (ft_strdup(stock_buff));
	line = malloc(i + 1);
	if (!line)
		return (NULL);
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
	int		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(read_buff, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, read_buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(read_buff), free(stock_buff), NULL);
		read_buff[bytes_read] = '\0';
		if (bytes_read)
			stock_buff = ft_strjoin(stock_buff, read_buff);
		if (!ft_strlen(stock_buff))
			return (free(read_buff), free(stock_buff), NULL);
	}
	free(read_buff);
	return (stock_buff);
}

char	*get_next_line(int fd)
{
	static char	*stock_buff;
	char		*read_buff;
	char		*line;
	int			linelen;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	read_buff = malloc(BUFFER_SIZE + 1);
	if (!read_buff)
		return (NULL);
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
