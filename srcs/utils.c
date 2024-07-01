/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:57:38 by adesille          #+#    #+#             */
/*   Updated: 2024/07/01 12:58:31 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_path(void)
{
	char	**path;
	char	*trimm_path;

	trimm_path = getenv("PATH");
	if (!trimm_path)
		return (NULL);
	path = ft_split(trimm_path, ':');
	return (path);
}

int	format_check(char *s, int *code)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (printf("minihell: %s: numeric argument required\n", s), 1);
	}
	if (*code)
	{
		if (*code > 255)
			*code -= 256;
		else if (code < 0)
			*code = 256 - -*code;
	}
	return (0);
}

char	*error_init(char *msg, char *file)
{
	char	*s;

	s = ft_strjoin(ft_strjoin("minihell: ", file), ": ");
	return (ft_strjoin(s, msg));
}

int	error(char *msg, char *file, int return_code)
{
	if (msg)
	{
		write(2, "minihell: ", ft_strlen("minihell: "));
		if (file)
		{
			write(2, file, ft_strlen(file));
			write(2, ": ", 2);
		}
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	if (return_code)
	{
		g_error_code = return_code;
		printf("error_code = %d\n", g_error_code);
		return (return_code);
	}
	return (1);
}

void	*ff(t_memman *mem_list)
{
	static char	heredoc[18] = "./srcs/parsing/hd0";
	t_memman	*temp;
	int			i;

	while (mem_list)
	{
		temp = mem_list;
		mem_list = mem_list->next;
		if (temp->type == FD)
			close(*(int *)temp->ptr);
		if (temp->ptr)
		{
			free(temp->ptr);
			temp->ptr = NULL;
		}
		free(temp);
	}
	i = -1;
	while (++i < 50)
	{
		heredoc[17] = i + '0';
		if (!access(heredoc, R_OK))
			unlink(heredoc);
	}
	return (NULL);
}
