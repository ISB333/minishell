/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:10:45 by adesille          #+#    #+#             */
/*   Updated: 2024/07/06 11:02:39 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prompt_data(t_prompt *data)
{
	if (data->curr_dir)
		free(data->curr_dir);
	if (data->root_dir)
		free(data->root_dir);
	if (data->pos)
		free(data->pos);
	if (data->name)
		free(data->name);
	free(data);
}

int	extract_pos(char **position)
{
	char	*trimm_path;
	int		i;

	trimm_path = ft_strtrim(getenv("SESSION_MANAGER"), "local/");
	if (!trimm_path)
		return (1);
	i = -1;
	while (trimm_path[++i] != '.')
		;
	*position = ft_substr(trimm_path, 0, i);
	if (!*position)
		return (free(trimm_path), 1);
	return (0);
}

char	*join_prompt(char *logname, char *position, char *curr_dir)
{
	char	*prompt;
	int		full_size;
	int		i;
	int		k;

	i = -1;
	k = -1;
	full_size = ft_strlen(logname) + ft_strlen(position)
		+ ft_strlen(curr_dir) + 5;
	prompt = mem_manager(full_size, 0, 0, 'A');
	if (!prompt)
		return (NULL);
	while (logname[++i])
		prompt[i] = logname[i];
	prompt[i] = '@';
	while (position[++k])
		prompt[++i] = position[k];
	prompt[++i] = ':';
	k = -1;
	while (curr_dir[++k])
		prompt[++i] = curr_dir[k];
	prompt[++i] = '$';
	prompt[++i] = ' ';
	prompt[++i] = '\0';
	return (prompt);
}

int	init_prompt_data(t_prompt *data, int start, int len, char *dir)
{
	data->name = ft_substr(getenv("LOGNAME"), 0, ft_strlen(getenv("LOGNAME")));
	if (!data->name)
		data->name = ft_substr("\0", 0, 1);
	if (!dir)
		return (1);
	data->curr_dir = ft_strdup(dir);
	if (extract_pos(&data->pos) && getenv("NAME"))
		data->pos = ft_substr(getenv("NAME"), 0, ft_strlen(getenv("NAME")));
	else if (!data->pos)
		data->pos = ft_substr("\0", 0, 1);
	data->root_dir = ft_strnstr(data->curr_dir, data->name,
			ft_strlen(data->curr_dir));
	if (data->root_dir)
	{
		start = ft_strlen(data->curr_dir) - ft_strlen(data->root_dir)
			+ ft_strlen(data->name);
		len = ft_strlen(data->root_dir) - ft_strlen(data->name);
		data->root_dir = ft_substr(data->curr_dir, start, len);
		if (!data->root_dir)
			return (1);
		data->curr_dir = ft_strjoin("~", data->root_dir);
	}
	return (0);
}

char	*get_prompt(void)
{
	t_prompt	*data;
	char		*prompt;

	data = mem_manager(sizeof(t_prompt), 0, 0, 'A');
	if (!data)
		return (NULL);
	data->curr_dir = NULL;
	data->root_dir = NULL;
	data->pos = NULL;
	if (init_prompt_data(data, 0, 0, get_cwdd(0, 0, 'G')))
		return (NULL);
	prompt = join_prompt(data->name, data->pos, data->curr_dir);
	if (!prompt)
		return (NULL);
	return (prompt);
}
