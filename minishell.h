/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:05 by adesille          #+#    #+#             */
/*   Updated: 2024/05/30 14:18:55 by nkieffer         ###   ########.fr       */
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


// typedef struct s_data
// {
// 	char **args;
// 	char 
// }	t_data;


char	*get_prompt(/*char *env[]*/void);
int		lexer(char *str);
char	**tokenizer(char const *s);

//sigHandler.c
int	catchBackslash(void);
int	catchC(void);

#endif