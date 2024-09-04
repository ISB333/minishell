/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:10:45 by adesille          #+#    #+#             */
/*   Updated: 2024/09/01 18:17:06 by isb3             ###   ########.fr       */
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
	prompt = mem_manager(full_size, 0, 0, ALLOCATE);
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
	data->name = ft_strrchr(get_cwdd(0, 0, HOME), '/') + 1;
	if (!data->name)
		data->name = ft_substr("\0", 0, 1);
	if (!dir)
		return (1);
	data->curr_dir = ft_strdup(dir);
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

char	*get_prompt(char *env[])
{
	t_prompt	*data;
	char		*prompt;
	static char *position = NULL;

	if (!*env)
		return (ft_strjoin(get_cwdd(0, 0, GET), "$ "));
	data = mem_manager(sizeof(t_prompt), 0, 0, ALLOCATE);
	if (!position)
	{
		position = get_envv(0, "SESSION_MANAGER", FIND);
		if (position)
		{
			position = ft_strchr(position, '/') + 1;
			position = ft_substr(position, 0, ft_strlen(position) - ft_strlen(ft_strchr(position, '.')));
		}
		else
			position = ft_strdup("\0");
	}
	data->curr_dir = NULL;
	data->root_dir = NULL;
	data->pos = position;
	if (init_prompt_data(data, 0, 0, get_cwdd(0, 0, GET)))
		return (NULL);
	prompt = join_prompt(data->name, data->pos, data->curr_dir);
	if (!prompt)
		return (NULL);
	return (prompt);
}
