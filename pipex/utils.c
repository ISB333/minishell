/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:41:35 by isb3              #+#    #+#             */
/*   Updated: 2024/04/14 14:37:54 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_memory(char **array)
{
	int	j;

	j = 0;
	if (!array)
		return ;
	while (array[j])
		j++;
	while (j-- > 0)
		free(array[j]);
	free(array);
}

int	ff(t_data *d, int err, char *msg)
{
	int	i;

	i = 0;
	if (err)
		write(2, strerror(err), ft_strlen(strerror(err)));
	if (msg)
	{
		write(1, ": ", 2);
		write(2, msg, ft_strlen(msg));
	}
	if (d->cmd_paths)
		free_memory(d->cmd_paths);
	close(d->infile);
	close(d->outfile);
	if (d->args)
	{
		while (d->args[i])
			i++;
		while (i-- > 0 && d->args[i])
			free_memory(d->args[i]);
		return (free(d->args), free(d), errno);
	}
	return (errno);
}

int	parse_cmds(t_data *d, char *argv[], char *cmd, int i)
{
	int		k;
	char	**cmds;

	k = -1;
	cmds = malloc((i - 2) * sizeof(char *));
	if (!cmds)
		return (-1);
	cmds[i - 3] = NULL;
	d->args[i - 3] = NULL;
	i = 2;
	while (argv[i + 1])
	{
		cmd = ft_strjoin(argv[i++], " ");
		if (!cmd)
			return (free_memory(cmds), -1);
		cmds[++k] = ft_substr(cmd, 0, ft_strlen(cmd));
		if (!cmds[k])
			return (free_memory(cmds), free(cmd), -1);
		free(cmd);
	}
	i = -1;
	while (cmds[++i])
		d->args[i] = ft_split(cmds[i], ' ');
	return (free_memory(cmds), 0);
}

int	parse_files(char *argv[], t_data *d)
{
	char	*file1;
	char	*file2;
	int		i;

	i = 1;
	file1 = ft_substr(argv[1], 0, ft_strlen(argv[1]));
	if (!file1)
		return (-1);
	while (argv[i])
		i++;
	file2 = ft_substr(argv[i - 1], 0, ft_strlen(argv[i - 1]));
	if (!file2)
		return (free(file1), -1);
	d->infile = open(file1, O_RDONLY);
	if (d->infile == -1)
		return (free(file1), free(file2), -1);
	d->outfile = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->outfile == -1)
		return (free(file1), free(file2), -1);
	return (free(file1), free(file2), 0);
}

int	initializer(t_data *d, char	*argv[], char *env[])
{
	int	i;

	i = 0;
	d->infile = 0;
	d->outfile = 0;
	d->cmd_paths = get_cmd_path(argv, env);
	if (!d->cmd_paths)
		return (free(d), 127);
	while (argv[i])
		i++;
	d->args = malloc((i - 2) * sizeof(char **));
	if (!d->args)
		return (-1);
	if (parse_cmds(d, argv, NULL, i))
		return (ff(d, 0, "args_parsing\n"), -1);
	i = 0;
	if (parse_files(argv, d))
		return (ff(d, 0, "files parsing\n"), -1);
	while (d->args[i])
		i++;
	d->it = 0;
	d->count = i;
	d->temp = -1;
	return (0);
}
