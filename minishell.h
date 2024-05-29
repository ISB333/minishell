/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:05 by adesille          #+#    #+#             */
/*   Updated: 2024/05/29 09:59:24 by adesille         ###   ########.fr       */
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


char	*get_prompt(char *env[]);
int		lexer(char *str);
char	**tokenizer(char *s);

int		is_sh_ope(char *s, int i);
int		is_del(char c);

#endif