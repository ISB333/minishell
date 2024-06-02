/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:10:45 by adesille          #+#    #+#             */
/*   Updated: 2024/06/02 13:40:54 by isb3             ###   ########.fr       */
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
	free(data);
}

int	extract_pos(char *env[], char **position)
{
	char	*trimm_path;
	int		i;

	i = 0;
	while (env[i] && (!strstr(env[i], "SESSION_MANAGER=")))
		i++;
	if (!env[i])
		return (1);
	trimm_path = ft_strtrim(env[i], "SESSION_MANAGER=local/");
	if (!trimm_path)
		return (1);
	i = -1;
	while (trimm_path[++i] != '.')
		;
	*position = ft_substr(trimm_path, 0, i);
	if (!*position)
		return (free(trimm_path), 1);
	return (free(trimm_path), 0);
}

char	*join_prompt(char *logname, char *position, char *curr_dir)
{
	char	*prompt;
	int		full_size;
	int		i;
	int		k;

	i = -1;
	k = -1;
	full_size = ft_strlen(logname) + ft_strlen(position) + \
		ft_strlen(curr_dir) + 5;
	prompt = malloc(full_size);
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

int	init_prompt_data(char *env[], t_prompt *data)
{
	int	start;
	int	len;

	start = 0;
	len = 0;
	data->logname = getenv("LOGNAME");
	data->curr_dir = getcwd(NULL, 0);
	if (!data->curr_dir)
		return (1);
	extract_pos(env, &data->pos);
	data->root_dir = ft_strnstr(data->curr_dir, data->logname, \
		ft_strlen(data->curr_dir));
	if (data->root_dir)
	{
		start = ft_strlen(data->curr_dir) - ft_strlen(data->root_dir) + \
			ft_strlen(data->logname);
		len = ft_strlen(data->root_dir) - ft_strlen(data->logname);
		data->root_dir = ft_substr(data->curr_dir, start, len);
		if (!data->root_dir)
			return (1);
		free(data->curr_dir);
		data->curr_dir = ft_strjoin("~", data->root_dir);
	}
	return (0);
}

char	*get_prompt(char *env[])
{
	t_prompt	*data;
	char		*prompt;

	data = malloc(sizeof(t_prompt));
	if (!data)
		return (NULL);
	data->curr_dir = NULL;
	data->root_dir = NULL;
	data->pos = NULL;
	if (init_prompt_data(env, data))
		return (free_prompt_data(data), NULL);
	if (!data->pos)
		data->pos = ft_substr(getenv("NAME"), 0, ft_strlen(getenv("NAME")));
	prompt = join_prompt(data->logname, data->pos, data->curr_dir);
	if (!prompt)
		return (free_prompt_data(data), NULL);
	return (free_prompt_data(data), prompt);
}
