/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:26:28 by adesille          #+#    #+#             */
/*   Updated: 2024/04/21 10:48:46 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft/libft.h"
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

# include <stdarg.h> /// ?????????? ///

typedef struct s_data
{
	char	***args;
	char	**cmd_paths;
	char	**files;
	pid_t	pid;
	int		count;
	int		it;
	int		pipe_fd[2];
	int		temp;
	int		infile;
	int		outfile;
}	t_data;

int		format_check(char *argv[]);
int		ff(t_data *d, int err, char *msg);
void	free_memory(char **array);
int		parse_files(char *argv[], t_data *d);

void	printer(t_data *d);
char	**get_cmd_path(char *argv[], char *env[]);
char	**extract_path(char *env[]);
int		initializer(t_data *d, char	*argv[], char *env[]);

int		pipex(char *argv[], char *env[]);

#endif
