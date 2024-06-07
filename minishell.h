/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:05 by adesille          #+#    #+#             */
/*   Updated: 2024/06/07 11:41:41 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include "libft/libft.h"

typedef	struct	s_prompt
{
	char	*logname;
	char	*position;
	char	*curr_dir;
	char	*root_dir;
}	t_prompt;	

typedef struct s_data
{
	char	*cmd_path;
	char	**args;
	int		pipe;
	int		infile;
	int		outfile;
}	t_data;

int	ft_do_all();


char	*get_prompt(void);
int		lexer(char *str);
char	**tokenizer(char *s);

int		is_sh_ope(char *s, int i);
int		is_del(char c);
size_t	count_rows(char *s);
char	*add_space(char *s, int i, int k);
char	**splitter(char **array, char *s, size_t i);

//sigHandler.c
int	catchBackslash(void);
int	catchC(void);

#endif